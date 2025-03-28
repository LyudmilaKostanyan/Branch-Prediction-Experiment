#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <iomanip>

using namespace std;
using namespace std::chrono;

vector<bool> generateRandomData(size_t size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    
    vector<bool> data(size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = dis(gen);
    }
    return data;
}

vector<bool> generatePredictableData(size_t size) {
    vector<bool> data(size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = (i % 2 == 0);
    }
    return data;
}

nanoseconds measureBranchPerformance(const vector<bool>& data, int iterations, volatile int& sum) {
    auto start = high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i]) {
                sum += 1;
            } else {
                sum += 2;
            }
        }
    }
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start);
}

int main() {
    const size_t SIZE = 10000000;
    const int ITERATIONS = 100;

    vector<bool> randomData = generateRandomData(SIZE);
    vector<bool> predictableData = generatePredictableData(SIZE);
    
    volatile int randomSum = 0;
    volatile int predictableSum = 0;
    
    auto randomDuration = measureBranchPerformance(randomData, ITERATIONS, randomSum);
    auto predictableDuration = measureBranchPerformance(predictableData, ITERATIONS, predictableSum);
    
    double randomMs = randomDuration.count() / 1000000.0;
    double predictableMs = predictableDuration.count() / 1000000.0;
    
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

    return 0;
}