# 6x6 Queens Dominating Set Solver

This project solves the **Queens Dominating Set** problem for a 6x6 board. 
It finds all configurations where the minimum number of queens (3) covers every square.

## Tech Stack
- **Language:** C++20
- **Optimization:** Bitboards (`uint64_t`), Precomputed attack masks, O3 Optimization.

## How to Build
Use a C++ compiler (like GCC 15.2):
```bash
g++ -O3 -std=c++20 main.cpp -o solver
./solver
