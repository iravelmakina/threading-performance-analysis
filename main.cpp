#include <iostream>
#include <thread>
#include <fstream>
#include <vector>

#include "Matrix.h"


// time of one regular thread
// time of threads list
// avg of 5

int numPhysicalCores = static_cast<int>(std::thread::hardware_concurrency());
int numLogicalCores = numPhysicalCores; // because there is no multithreading on my cpu

int main() {
    const std::vector sizes = {50, 100, 500, 1000, 10000};
    const std::vector threadCounts = {
        numPhysicalCores / 2, numPhysicalCores, numLogicalCores,
        numLogicalCores * 2, numLogicalCores * 4, numLogicalCores * 8, numLogicalCores * 16, 1000, 5000 };

    std::ofstream csvFile("threadPerformance.csv");

    csvFile << "MatrixSize,Threads,Time\n";

    for (const int size : sizes) {
        std::cout << "\nMatrix size: " << size << "x" << size << std::endl;

        Matrix m(size);

        Matrix singleThreadedMatrix = m;
        Matrix multiThreadedMatrix = m;

        const auto startSingle = std::chrono::high_resolution_clock::now();
        singleThreadedMatrix.transposeSingleThreaded();
        const auto endSingle = std::chrono::high_resolution_clock::now();

        const long long elapsedSingle = std::chrono::duration_cast<std::chrono::nanoseconds>(endSingle - startSingle).count();
        std::cout << "Single-threaded: Time taken: " << elapsedSingle * 1e-9 << " seconds or " << elapsedSingle << " nanoseconds." << std::endl;
        csvFile << size << ",1," << elapsedSingle * 1e-9 << "\n";

        for (const int numThreads : threadCounts) {
            multiThreadedMatrix = m;
            const auto startMulti = std::chrono::high_resolution_clock::now();
            multiThreadedMatrix.transposeMultiThreaded(numThreads);
            const auto endMulti = std::chrono::high_resolution_clock::now();

            const long long elapsedMulti = std::chrono::duration_cast<std::chrono::nanoseconds>(endMulti - startMulti).count();
            std::cout << "Threads: " << numThreads << ", Time taken: " << elapsedMulti * 1e-9 << " seconds or " << elapsedMulti << " nanoseconds." << std::endl;
            csvFile << size << "," << numThreads << "," << elapsedMulti * 1e-9 << "\n";
        }
    }
    return 0;
};
