#include <iostream>
#include <thread>
#include <fstream>
#include <numeric>
#include <vector>

#include "Matrix.h"


int numPhysicalCores = static_cast<int>(std::thread::hardware_concurrency());
int numLogicalCores = numPhysicalCores; // because there is no hyper threading on my CPU
const std::vector sizes = {50, 100, 500, 1000, 10000};
const std::vector threadCounts = {
    numPhysicalCores / 2, numPhysicalCores = numLogicalCores, 10,
    numLogicalCores * 2, numLogicalCores * 4, numLogicalCores * 8, numLogicalCores * 16, 256, 512, 1024, 2048 };


int main() {
    std::ofstream csvFile("./data/threadPerformance.csv");
    csvFile << "MatrixSize,Threads,AvgTime\n";

    for (const int size : sizes) {
        constexpr int repetitions = 5;
        std::cout << "\nMatrix size: " << size << "x" << size << std::endl;

        Matrix originalMatrix(size);

        {
            std::vector<double> times;
            for (int i = 0; i < repetitions; ++i) {
                Matrix m = originalMatrix;
                const auto start = std::chrono::high_resolution_clock::now();
                m.transposeSingleThreaded();
                const auto end = std::chrono::high_resolution_clock::now();

                const long long elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                times.push_back(elapsed * 1e-9);
            }
            double avgTime = std::accumulate(times.begin(), times.end(), 0.0) / repetitions;
            std::cout << "Single-threaded: Avg time: " << avgTime << " seconds." << std::endl;
            csvFile << size << ",1," << avgTime << "\n";
        }

        for (const int numThreads : threadCounts) {
            std::vector<double> times;
            for (int i = 0; i < repetitions; ++i) {
                Matrix m = originalMatrix;
                const auto start = std::chrono::high_resolution_clock::now();
                m.transposeMultiThreaded(numThreads);
                const auto end = std::chrono::high_resolution_clock::now();

                const long long elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                times.push_back(elapsed * 1e-9);
            }
            double avgTime = std::accumulate(times.begin(), times.end(), 0.0) / repetitions;
            std::cout << "Threads: " << numThreads << ", Avg time: " << avgTime << " seconds." << std::endl;
            csvFile << size << "," << numThreads << "," << avgTime << "\n";
        }
    }
    csvFile.close();
    return 0;
}

