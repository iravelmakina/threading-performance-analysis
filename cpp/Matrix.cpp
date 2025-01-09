#include "Matrix.h"

#include <iostream>
#include <thread>


Matrix::Matrix(int const size) : size(size), matrix(size, std::vector<int>(size)) {
    for (size_t row = 0; row < size; ++row) {
        for (size_t col = 0; col < size; ++col) {
            matrix[row][col] = rand() % 100 + 1;
        }
    }
}


void Matrix::transposeSingleThreaded() {
    for (size_t row = 0; row < size; ++row) {
        for (size_t col = row + 1; col < size; ++col) { // only upper triangular part
            std::swap(matrix[row][col], matrix[col][row]);
        }
    }
}


void Matrix::transposeMultiThreaded(const int numThreads) {
    std::vector<std::thread> threads;
    const int chunkSize = (size + numThreads - 1) / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        const int startRow = t * chunkSize;
        int endRow = std::min(startRow + chunkSize, size);

        threads.emplace_back([this, startRow, endRow]() {
            for (size_t row = startRow; row < endRow; ++row) {
                for (size_t col = row + 1; col < size; ++col) {
                    std::swap(matrix[row][col], matrix[col][row]);
                }
            }
        });
    }

    for (std::thread& thread : threads) {
        thread.join();
    }
}


void Matrix::display() const {
    for (size_t row = 0; row < size; ++row) {
        for (size_t col = 0; col < size; ++col) {
            if (matrix[row][col] < 10) {
                std::cout << "  ";
            } else if (matrix[row][col] < 100) {
                std::cout << " ";
            }

            std::cout << matrix[row][col] << " ";
        }
        std::cout << std::endl;
    }
}
