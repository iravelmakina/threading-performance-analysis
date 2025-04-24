# Matrix Transposition Performance Analysis

This project analyzes the performance of matrix transposition algorithms using multi-threading. It includes a C++ program for measuring the average execution time of matrix transposition for various matrix sizes and thread counts, as well as a Python script to visualize the results.

---

## **Features**
### **C++ Program**
- Measures matrix transposition execution time for:
  - Single-threaded execution.
  - Multi-threaded execution with varying thread counts.
- Writes performance statistics to a CSV file.

### **Python Script**
- Reads the generated CSV file and creates a performance graph.
- Visualizes the relationship between the number of threads and execution time for different matrix sizes.

---

## **Project Structure**

- `cpp/`
  - `main.cpp` - Main program to measure transposition performance
  - `Matrix.cpp` - Matrix class implementation
  - `Matrix.h` - Matrix class definition
- `data/` – Will appear if not created
  - `threadPerformance.csv` - Generated CSV with performance data will appear here
  - `thread_scaling_graph.png` - Generated performance graph will appear here
- `scripts/`
  - `graph.py` - Python script to generate performance graph
- `.gitignore` - Excludes unnecessary files from version control
- `CMakeLists.txt` - CMake build configuration
- `requirements.txt` - Python dependencies
- `README.md` - Project documentation


---

## **Setup and Usage**

### **1. Clone the Repository**
```bash
git clone <repository-url>
cd <repository-name>
```

### **2. Build and Run the C++ Program**

#### Requirements
- C++20 compatible compiler
- CMake (version 3.10 or later)

#### Steps
1. Create a build directory and configure the project:
    ```bash
    cmake -S . -B cmake-build-release
    cmake --build cmake-build-release
    ```

2. Run the executable:
    ```bash
    ./cmake-build-release/threads-basic
    ```

#### Output:
Performance statistics are saved in `data/threadPerformance.csv`.

### **3. Generate Performance Graph**

#### Requirements
- Python 3.x
- Required Python libraries are listed in `requirements.txt`.

#### Steps
1. Set up a virtual environment:
    ```bash
    python3 -m venv venv
    source venv/bin/activate
    ```

2. Install dependencies:
    ```bash
    pip install -r requirements.txt
    ```

3. Run the script:
    ```bash
    python scripts/graph.py
    ```

#### Output:
The graph is displayed and saved as `data/thread_scaling_graph.png`.

---

## **Performance Metrics**

The program evaluates the following:
- Execution time for single-threaded and multi-threaded matrix transposition.
- Comparison across different matrix sizes (50x50, 100x100, 500x500, 1000x1000, 10000x10000).
- Variation in performance with varying thread counts:
  - Half the number of physical cores.
  - Equal to physical cores.
  - Equal to logical cores.
  - 2x, 4x, 8x, and 16x logical cores.

### **Output Example**

#### CSV File (`data/threadPerformance.csv`)
```
MatrixSize,Threads,AvgTime
50,1,0.005
50,2,0.003
100,1,0.020
100,2,0.015
...
```

#### Graph (`data/thread_scaling_graph.png`)
The graph shows:
- Execution time vs. number of threads.
- Separate curves for each matrix size.
- Annotations marking the optimal thread count for each size.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Contributor

- [@iravelmakina](https://github.com/iravelmakina)
