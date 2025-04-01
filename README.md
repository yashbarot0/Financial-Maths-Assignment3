# Monte Carlo European Option Pricer

This repository contains two implementations of a Monte Carlo pricer for European call options:
1. **Serial Implementation**: A single-threaded version.
2. **Parallel Implementation**: A multi-threaded version using OpenMP.

## Overview

The Monte Carlo method is used to estimate the price of a European call option by simulating multiple paths of the underlying asset's price and averaging the discounted payoffs.

### Key Features
- **Serial Version**: Simple implementation using a single thread.
- **Parallel Version**: Leverages OpenMP for parallelization to improve performance.

## Dependencies
- **GNU Scientific Library (GSL)**: Required for random number generation.
- **C++ Compiler**: Supports C++11 or later (e.g., GCC, Clang).

## Building the Programs

### Prerequisites
- Install GSL:
    ```
  - **macOS (using Homebrew)**:
    ```bash
    brew install gsl
    ```

### Using the Makefile
1. **Compile Both Programs**:
   ```bash
   make

### Run the Program 
./monte_carlo_pricer
./monte_carlo_pricer_omp


### Output
### Serial Version
European Call Option Price: 10.4459
Execution Time: 0.0608773 seconds
### Parallel Version
European Call Option Price: 10.4333
Execution Time: 0.0218687 seconds