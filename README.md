# Linear Algebra API in C++

## Overview
This project provides a **modular and scalable API** implemented in **C++** for performing **linear algebra operations** such as matrix manipulations and vector computations. It is designed for **high-performance computing (HPC)** applications, leveraging external libraries like **Hypre** and **PETSc** to support distributed computations.

The API focuses on **precision**, **scalability**, and **performance optimization**, making it suitable for scientific simulations and large-scale numerical computations.

---

## Features
- **Basic Linear Algebra Operations:**
  - Matrix multiplication, addition, and transposition.
  - Vector arithmetic and transformations.
- **Integration with Third-Party Libraries:**
  - **Hypre** and **PETSc** for advanced linear algebra and distributed computing.
- **Parallel Computing Support:**
  - Compatible with **MPI** for distributed processing.
  - Utilizes **OpenMP** for multi-threading.
- **Performance Optimization:**
  - Exploits SIMD instructions (SSE/AVX).
  - Optimized memory management and cache utilization.
- **Testing and Examples:**
  - Predefined examples and tests for verifying the functionality of the API.

---

## File Structure
```
├── src/                        # Source code files
│   ├── GenericExample.cpp      # Examples for basic operations
│   ├── HypreExample.cpp        # Example using Hypre library
│   ├── PETScExample.cpp        # Example using PETSc library
│   ├── Test.cpp                # Test cases
│   ├── AlienMock.h             # Mock interface for Alien library
│   ├── MpiMock.h               # Mock interface for MPI
│   └── main.cpp                # Entry point
├── CMakeLists.txt              # Build configuration
└── README.md                   # Documentation
```

---

## Requirements
- **C++ Compiler:** GCC 7.5+ or Clang 10+.
- **CMake:** Version 3.10 or later.
- **MPI Library:** OpenMPI or MPICH.
- **Libraries:**
  - **Hypre** (for sparse matrices and parallel solvers).
  - **PETSc** (for scalable linear and nonlinear solvers).
- **Operating System:** Linux or macOS (Windows requires WSL).

---

## Installation
1. Clone the repository:
```bash
$ git clone https://github.com/ChadhaSakka/Linear-Algebra-API.git
$ cd Linear-Algebra-API
```
2. Build the project:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```
3. Run examples:
```bash
$ ./GenericExample
$ ./HypreExample
$ ./PETScExample
```

---

## Usage
### Example: Basic Matrix Multiplication
```cpp
#include "GenericExample.h"

Matrix A(3, 3);  // 3x3 matrix
Matrix B(3, 3);
Matrix C;

// Initialize matrices
A.randomize();
B.randomize();

// Perform multiplication
C = A * B;
C.print();
```
### Example: Parallel Computation with MPI
```cpp
#include "MpiMock.h"
MPI_Init(NULL, NULL);
// Distributed computation
MPI_Finalize();
```

---

## Tests
Run tests to validate the implementation:
```bash
$ ./Test
```

---

## Performance Optimization
- **SIMD Vectorization:** Uses AVX and SSE instructions for faster computations.
- **Parallelization:** OpenMP for CPU parallelism and MPI for distributed computation.
- **Memory Management:** Dynamic allocation with prefetching and cache optimization.

---

## Future Improvements
- Support for **GPU computing** using CUDA or OpenCL.
- **Sparse matrix operations** for large-scale problems.
- Improved **documentation** and API examples.
- Extensions for **machine learning algorithms**.

---

## License
This project is licensed under the **MIT License**.

---

