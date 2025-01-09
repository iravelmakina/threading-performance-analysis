#pragma once
#include <vector>

class Matrix {
public:
    explicit Matrix(int size);

    void transposeSingleThreaded();

    void transposeMultiThreaded(int numThreads);

    void display() const;
private:
    int size;
    std::vector<std::vector<int> > matrix;
};

