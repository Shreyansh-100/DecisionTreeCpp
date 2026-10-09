FROM python:3.12-slim-bookworm AS engine
RUN apt-get update && apt-get install -y --no-install-recommends g++ && rm -rf /var/lib/apt/lists/*
WORKDIR /build
COPY Dtree/*.cpp Dtree/*.h ./
RUN g++ -std=c++17 -O2 Main.cpp data_handler.cpp decision_tree.cpp inference.cpp -o dtree

FROM python:3.12-slim-bookworm
ENV PYTHONDONTWRITEBYTECODE=1 PYTHONUNBUFFERED=1 PORT=10000
WORKDIR /app
COPY backend/requirements.txt backend/requirements.txt
RUN pip install --no-cache-dir -r backend/requirements.txt
COPY backend/main.py backend/main.py
COPY --from=engine /build/dtree Dtree/dtree
RUN useradd --uid 10001 --create-home appuser
USER appuser
EXPOSE 10000
CMD ["sh", "-c", "exec uvicorn backend.main:app --host 0.0.0.0 --port ${PORT:-10000}"]
