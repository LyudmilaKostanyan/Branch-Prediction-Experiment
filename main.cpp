#include <iostream>
#include <vector>
#include <iomanip>
#include "kaizen.h"

using namespace std;
using namespace std::chrono;

vector<int> generateRandomData(size_t size) {
    vector<int> data(size);
    for (size_t i = 0; i < size; ++i)
        data[i] = zen::random_int(-10000000, 10000000);
    return data;
}

vector<int> generatePredictableData(size_t size) {
    vector<int> data(size);
    for (size_t i = 0; i < size; ++i)
        data[i] = i;
    return data;
}

auto measureBranchPerformance(const vector<int>& data, int iterations, volatile int& sum) {
    zen::timer timer;
    timer.start();
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] < 0)
                sum += 1;
            else
                sum += 2;
        }
    }
    timer.stop();
    return timer.duration<zen::timer::msec>();
}

void printResults(double randomMs, double predictableMs) {
    double speedup = randomMs / predictableMs;
    double difference = randomMs - predictableMs;
    
    cout << setfill('-') << setw(85) << "" << endl;
    cout << setfill(' ') << left
         << setw(15) << "     " 
         << setw(22) << "Unpredictable (ms)" 
         << setw(20) << "Predictable (ms)" 
         << setw(15) << "Speedup (x)"
         << "Difference" << endl;
    cout << setfill('-') << setw(85) << "" << endl;
    cout << setfill(' ') << left
         << setw(17) << "Access Time" 
         << setw(22) << fixed << setprecision(2) << randomMs
         << setw(20) << predictableMs
         << setw(15) << setprecision(2) << speedup
         << difference << endl;
    cout << setfill('-') << setw(85) << "" << endl;
}

int main() {
    const size_t SIZE = 10000000;
    const int ITERATIONS = 100;

    vector<int> randomData = generateRandomData(SIZE);
    vector<int> predictableData = generatePredictableData(SIZE);
    
    volatile int randomSum = 0;
    volatile int predictableSum = 0;
    
    auto randomDuration = measureBranchPerformance(randomData, ITERATIONS, randomSum);
    auto predictableDuration = measureBranchPerformance(predictableData, ITERATIONS, predictableSum);
    
    double randomMs = randomDuration.count();
    double predictableMs = predictableDuration.count();
    
    printResults(randomMs, predictableMs);

    return 0;
}