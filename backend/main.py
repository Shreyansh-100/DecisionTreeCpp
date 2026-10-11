import logging
import os
from pathlib import Path
import subprocess
import tempfile
from fastapi import FastAPI, File, HTTPException, UploadFile
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse
from starlette.background import BackgroundTask

app = FastAPI()
app.add_middleware(
    CORSMiddleware,
    allow_origins=[origin.strip().rstrip('/') for origin in os.getenv(
        'ALLOWED_ORIGINS', 'http://localhost:5173,http://127.0.0.1:5173'
    ).split(',') if origin.strip()],
    allow_methods=['POST'],
    allow_headers=['*'],
)
EXECUTABLE = Path(__file__).resolve().parent.parent / 'Dtree' / 'dtree'
MAX_UPLOAD_BYTES = int(os.getenv('MAX_UPLOAD_BYTES', str(10 * 1024 * 1024)))
PREDICTION_TIMEOUT_SECONDS = int(os.getenv('PREDICTION_TIMEOUT_SECONDS', '60'))

@app.get('/health')
def health():
    if not EXECUTABLE.is_file() or not os.access(EXECUTABLE, os.X_OK):
        raise HTTPException(503, 'Decision tree engine unavailable')
    return {'status': 'ok'}

@app.post('/predict')
def predict(file: UploadFile = File(...)):
    if Path(file.filename or '').suffix.lower() != '.csv':
        raise HTTPException(400, 'Please upload a CSV file')
    workspace = tempfile.TemporaryDirectory(prefix='dtree-')
    try:
        input_csv = Path(workspace.name) / 'input.csv'
        output_csv = Path(workspace.name) / 'prediction.csv'
        size = 0
        with input_csv.open('wb') as buffer:
            while chunk := file.file.read(1024 * 1024):
                size += len(chunk)
                if size > MAX_UPLOAD_BYTES:
                    raise HTTPException(413, 'CSV exceeds the upload size limit')
                buffer.write(chunk)
        if size == 0:
            raise HTTPException(400, 'CSV file is empty')
        try:
            subprocess.run(
                [str(EXECUTABLE), str(input_csv), str(output_csv)],
                check=True, timeout=PREDICTION_TIMEOUT_SECONDS,
                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
            )
        except subprocess.TimeoutExpired:
            raise HTTPException(504, 'Training exceeded the time limit')
        except subprocess.CalledProcessError:
            raise HTTPException(422, 'The engine could not process this dataset')
        except OSError:
            logging.exception('Unable to start decision tree engine')
            raise HTTPException(503, 'Decision tree engine unavailable')
        if not output_csv.is_file():
            raise HTTPException(500, 'The engine did not generate a report')
        return FileResponse(
            output_csv, filename='prediction.csv', media_type='text/csv',
            background=BackgroundTask(workspace.cleanup),
        )
    except BaseException:
        workspace.cleanup()
        raise
    finally:
        file.file.close()
