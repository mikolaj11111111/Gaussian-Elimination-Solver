# Gaussian Elimination Solver

## Description
Solves systems of linear equations using Gaussian elimination with partial pivoting. Processes multiple input files and saves step-by-step solutions.

## Features
- **Gaussian Elimination** - Forward elimination with partial pivoting
- **Partial Pivoting** - Improves numerical stability by selecting largest pivot
- **Back Substitution** - Computes final solution from reduced matrix
- **File Processing** - Handles multiple test cases automatically
- **Step Visualization** - Shows matrix reduction progress
- **Result Export** - Saves reduced matrices to output files

## Mathematical Background
- **Gaussian Elimination**: Transforms system Ax = b to upper triangular form
- **Partial Pivoting**: Reduces numerical errors by choosing optimal pivot elements
- **Back Substitution**: Solves triangular system from bottom to top

## Input Format
Files should contain:
```
N = [matrix size]
b: [vector values]
A: [matrix rows]
```

## Usage
Processes files: `gauss_elimination_gr1IO_A.txt`, `gauss_elimination_gr1IO_B.txt`, `gauss_elimination_gr1IO_C.txt`
Outputs reduced matrices to `*_reduced.txt` files.
