from pathlib import Path
import subprocess
from fastapi import FastAPI,UploadFile,File,HTTPException
from fastapi.middleware.cors import CORSMiddleware
import shutil
import subprocess
import uuid
from pathlib import Path
from fastapi.responses import FileResponse


app=FastAPI()
ALLOWED_EXTENSIONS={".csv"}
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:5173","http://127.0.0.1:5173"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)



BASE_DIR = Path(__file__).resolve().parent

UPLOAD_DIR = BASE_DIR / "uploads"
OUTPUT_DIR = BASE_DIR / "outputs"

UPLOAD_DIR.mkdir(exist_ok=True)
OUTPUT_DIR.mkdir(exist_ok=True)

# executable
EXECUTABLE = BASE_DIR.parent / "Dtree" / "dtree"



@app.post("/predict")
async def predict(file: UploadFile = File(...)):

    # unique filenames
    uid = uuid.uuid4().hex

    input_csv = UPLOAD_DIR / f"{uid}.csv"
    output_csv = OUTPUT_DIR / f"{uid}_prediction.csv"

    # save uploaded file
    with open(input_csv, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)

    # execute C++ program
    subprocess.run(
        [
            str(EXECUTABLE),
            str(input_csv),
            str(output_csv)
        ],
        check=True
    )

    # return prediction csv
    return FileResponse(
        path=output_csv,
        filename="prediction.csv",
        media_type="text/csv"
    )

