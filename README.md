# Decision Tree Classifier (C++ + React + FastAPI)

## Overview

This project is a Binary  Decision Tree Classifier that allows users to upload a CSV dataset, train a Decision Tree model implemented entirely in **C++**, and download a comprehensive report containing both model evaluation metrics and the generated decision tree.

The application combines a modern React frontend, a FastAPI backend, and a custom C++ implementation to provide an interactive interface for training and evaluating decision tree models.

> **Disclaimer:** This project was developed as a learning project for educational purposes. It is not intended for production use and is continuously being improved.

---

## CLI & Web Application

This repository contains **two ways** to use the Decision Tree Classifier.

### Command Line Interface (CLI)

The CLI application is the core implementation of the project. Users can execute the C++ program directly from the terminal by providing a CSV dataset and updating the path in data_handler.cpp file . The application trains the Decision Tree, evaluates the model, computes performance metrics, and exports a prints the details  containing both the evaluation metrics and the generated decision tree on the CLI itself.

### Web Application

The web application extends the CLI by integrating the same C++ executable with a FastAPI backend and a React frontend.

Users can upload datasets through the browser, while the backend invokes the C++ engine to train the model and generate the report. The generated CSV is then automatically downloaded by the user.

Both interfaces use the **same Decision Tree implementation**, ensuring consistency while keeping the machine learning logic independent from the user interface.

---

## Features

- Decision Tree algorithm implemented completely in C++
- Standalone CLI application
- Modern React frontend
- FastAPI backend
- CSV dataset upload
- Automatic model evaluation
- Downloadable CSV report containing:
  - Accuracy
  - Precision (Binary Classification)
  - Recall (Binary Classification)
  - F1 Score (Binary Classification)
  - Complete Decision Tree structure
- Terminal-inspired web interface
- Native C++ execution for improved performance

---

## Tech Stack

### Frontend

- React
- Axios
- CSS

### Backend

- FastAPI
- Python

### Core Algorithm

- C++

---

## Project Workflow

### CLI Workflow

```
CSV Dataset
      │
      ▼
 C++ Decision Tree
      │
      ▼
 Model Evaluation
      │
      ▼
 CSV Report
```

### Web Application Workflow

```
React Frontend
       │
       ▼
FastAPI Backend
       │
       ▼
C++ Decision Tree Engine
       │
       ▼
Generated CSV Report
       │
       ▼
Automatic Download
```

---

## Report Output

The generated report includes:

- Accuracy
- Precision
- Recall
- F1 Score


---

## Running the Project

### Backend

```bash
cd backend
uvicorn main:app --reload
```

### Frontend

```bash
cd frontend
npm install
npm run dev
```

### CLI

Compile the C++ source and execute the binary:

```bash
./dtree input.csv output.csv
```

where:

- `input.csv` is the dataset.
- `output.csv` is the generated report.

---

## Future Improvements

- Interactive Decision Tree visualization
- Support for Regression Trees
- Feature Importance visualization
- Hyperparameter configuration
- Additional evaluation metrics
- Drag-and-drop dataset upload

---

## License

This project is intended for educational, internship, and demonstration purposes.