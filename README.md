# Branch Prediction Experiment

## Overview
This program is designed to quantify the performance impact of branch mispredictions in modern CPUs by comparing the execution time of two loops: one with an unpredictable branching pattern and another with a predictable branching pattern. Branch mispredictions occur when a CPU's branch predictor fails to correctly guess the outcome of a conditional statement, leading to pipeline stalls and performance degradation. This experiment highlights the cost of such mispredictions, a critical factor in speculative execution.

### Problem Description
Modern CPUs use branch prediction to optimize performance by guessing the outcome of conditional statements (e.g., `if` statements) before they are fully evaluated. When the prediction is correct, execution proceeds smoothly. However, when the prediction is wrong, the CPU must discard speculative work and reload the correct instructions, incurring a performance penalty. This experiment measures this penalty by:
- Generating a dataset with random values (unpredictable branching).
- Generating a dataset with sequential values (predictable branching).
- Running a loop with a conditional statement (`if data[i] < 0`) on both datasets and measuring execution time.

## Code Structure
- **generateRandomData(size_t size)**: Creates a vector of random integers between -10,000,000 and 10,000,000 to simulate unpredictable branching.
- **generatePredictableData(size_t size)**: Creates a vector of sequential integers (0, 1, 2, ...) to simulate predictable branching.
- **measureBranchPerformance(const vector<int>& data, int iterations, volatile int& sum)**: Measures the time taken to execute a loop with a conditional statement over the dataset for a specified number of iterations. The `volatile` keyword prevents compiler optimizations from skewing results.
- **printResults(double randomMs, double predictableMs)**: Displays the execution times, speedup factor, and time difference in a formatted table.
- **main()**: Sets up the experiment with a dataset size of 10,000,000 and 100 iterations, runs the performance tests, and outputs the results.

## Example Output
```
-------------------------------------------------------------------------------------
                Unpredictable (ms)    Predictable (ms)    Speedup (x)    Difference
-------------------------------------------------------------------------------------
Access Time      3576.00               516.00              6.93           3060.00
-------------------------------------------------------------------------------------
```
- **Unpredictable (ms)**: Time taken for the loop with random data (e.g., 3576 ms).
- **Predictable (ms)**: Time taken for the loop with sequential data (e.g., 516 ms).
- **Speedup (x)**: Ratio of unpredictable to predictable time (e.g., 6.93x slower for unpredictable).
- **Difference**: Absolute time difference (e.g., 3060 ms).

## Explanation of Performance Difference
The significant difference in execution times (e.g., 3576 ms vs. 516 ms) arises due to branch prediction efficiency:
- **Unpredictable Case**: The random data causes the condition `if (data[i] < 0)` to alternate unpredictably between true and false. Since the branch predictor cannot reliably guess the outcome, mispredictions occur frequently, leading to pipeline flushes and higher execution time.
- **Predictable Case**: The sequential data (all positive integers starting from 0) ensures the condition `if (data[i] < 0)` is always false. The branch predictor can easily predict this consistent pattern, minimizing mispredictions and allowing the CPU to execute the loop efficiently.
- **Speedup**: The speedup (e.g., 6.93x) quantifies how much slower the unpredictable case is due to branch misprediction overhead. The difference (e.g., 3060 ms) represents the raw cost of these mispredictions.

## How to Compile and Run the Code
This section assumes the code is part of a repository and uses CMake for building, as implied by your provided build instructions. Adjust the repository URL and directory names as needed.

1. **Clone the Repository**:
   If you haven't cloned the repository yet, do so by running:
   ```
   git clone https://github.com/username/Branch-Prediction-Experiment.git
   cd Branch-Prediction-Experiment
   ```

2. **Build the Project**:
   Once in the project directory, compile the code with CMake:
   ```
   cmake -S . -B build
   cmake --build build
   ```
   This generates the executable in the `build` directory. Note: Ensure you have CMake, a C++ compiler (e.g., g++), and the required libraries (e.g., standard C++ library) installed.

3. **Run the Compiled Executable**:
   After building, run the program:
   ```
   cd build
   ./main  # On Windows, use `main.exe`
   ```
