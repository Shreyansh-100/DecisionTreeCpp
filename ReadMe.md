# Decision Tree Classifier — OOP C++ Project

This repository contains an undergraduate Object-Oriented Programming (C++) project that implements a simple decision tree classifier. The goal is to demonstrate OOP design, file organization, and a working classification pipeline (data loading, tree training, and inference) in idiomatic C++.

## Highlights
- Small, self-contained C++ project suitable for learning and demonstration.
- Clear separation of responsibilities across classes/files.
- Uses a CSV dataset (`read.csv`) for training/testing.

## Files
All source files are in the project root:

- `data_handler.h` / `data_handler.cpp` — loading and preprocessing CSV data; splitting features/labels and providing data structures used by the tree.
- `decision_tree.h` / `decision_tree.cpp` — decision tree implementation (building the tree from data, choosing splits, storing nodes).
- `inference.h` / `inference.cpp` — code to run the trained tree on new examples and compute predictions.
- `Main.cpp` — program entry point: ties everything together (loads data, trains the tree, runs inference, prints results).
- `read.csv` — example dataset used by the project (small CSV for demonstration).

> Note: File-level responsibilities are intentionally simple so you can inspect and extend them as part of an OOP assignment.

## Design / OOP Concepts
This project is structured around a few focused classes (one per pair of header/source files). Typical responsibilities:

- DataHandler: encapsulates CSV parsing, data storage (features/labels), and any basic preprocessing.
- DecisionTree: builds and stores a tree structure (nodes with split criteria and leaf predictions). Training logic and node splitting live here.
- Inference: accepts a trained tree and one or more samples to produce predicted labels.

The project demonstrates encapsulation, separation of concerns, and simple modular design suitable for extension (adding pruning, different split criteria, or metrics).

## Build (Linux)
This project uses plain C++ and no external libraries. You can compile it with g++ (C++17 recommended):

```bash
cd /path/to/DecisionTreeCpp
g++ -std=c++17 -O2 Main.cpp data_handler.cpp decision_tree.cpp inference.cpp -o decision_tree
```

Replace `/path/to/DecisionTreeCpp` with the actual workspace path. If compilation fails, check that all source files exist in the same directory and your compiler supports C++17.

## Run
If the program reads `read.csv` by default, simply run:

```bash
./decision_tree
```

If `Main.cpp` accepts a command-line argument for a CSV path, you can run:

```bash
./decision_tree path/to/your.csv
```

If the program does not currently accept a path, edit `Main.cpp` to add argument parsing or replace the filename used in the source.

## Expected Output
When run, the program trains a decision tree on the provided CSV and prints training / inference information to the console (for example: tree structure, predictions, accuracy). Exact output depends on the implementation in `Main.cpp`.

## Dataset (`read.csv`)
The repository includes a small example dataset named `read.csv`. Inspect it to understand the expected format (header row, feature columns, label column). If you add your own CSV, make sure it matches the same column ordering and delimiter.

## Assumptions
- The project uses a small, in-repo CSV for demonstration.
- No external libraries or package managers are required.
- The splitting criterion (information gain / Gini / other) is implemented inside `decision_tree.cpp` — refer to the file for mathematical details.

## How to Extend (suggestions for coursework)
1. Add unit tests for `DataHandler` (CSV parsing edge cases) and for small trees.
2. Implement pruning (pre- or post-pruning) to reduce overfitting.
3. Add support for continuous-valued features and thresholding.
4. Report evaluation metrics (accuracy, precision, recall) on a held-out test set.
5. Add CLI flags for dataset path, max depth, min samples per leaf, and output verbosity.

## Known Limitations
- Not optimized for large datasets (in-memory CSV parsing and recursive tree building may be slow on big inputs).
- No cross-validation or automated hyperparameter tuning included.

## Quick checklist (for the lab report)
- Explain the class responsibilities and how they communicate.
- Show sample runs and console output.
- Describe any assumptions and limitations.
- Propose one or two extensions and show how you would implement them (class/method-level notes).

## Author & License
Undergraduate OOP project. Replace this section with your name and any licensing information required by your course or institution.

---

