#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>

using namespace std;

// Function to multiply matrices using block partitioning
vector<vector<int>> blockMatrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B, int blockSize) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();

    vector<vector<int>> C(m, vector<int>(p, 0));

    for (int i0 = 0; i0 < m; i0 += blockSize) {
        for (int j0 = 0; j0 < p; j0 += blockSize) {
            for (int k0 = 0; k0 < n; k0 += blockSize) {
                int i_max = min(i0 + blockSize, m);
                int j_max = min(j0 + blockSize, p);
                int k_max = min(k0 + blockSize, n);

                for (int i = i0; i < i_max; i++) {
                    for (int j = j0; j < j_max; j++) {
                        int sum = C[i][j];
                        for (int k = k0; k < k_max; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }

    return C;
}

int getRandom() {
    static std::random_device rd; 
    static std::mt19937 eng(rd()); 
    std::uniform_int_distribution<> distr(0, 99);
    return distr(eng);
}

// Function to generate a random matrix
vector<vector<int>> generateRandomMatrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = getRandom();  // Random integers between 0 and 99
        }
    }
    return matrix;
}

// Function to print a matrix (only for small matrices)
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

double measureExecutionTime(const vector<vector<int>>& A, const vector<vector<int>>& B, int blockSize) {
    auto start = chrono::steady_clock::now();
    blockMatrixMultiply(A, B, blockSize);
    auto end = chrono::steady_clock::now();
    double cpu_time_used = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    return cpu_time_used;
}

int main(int argc, char* argv[]) {
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " m n p" << endl;
        return EXIT_FAILURE;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int p = atoi(argv[3]);
    //matrix dimensions
    cout << "m: " << m << endl;
    cout << "n: " << n << endl;
    cout << "p: " << p << endl;

    vector<vector<int>> A = generateRandomMatrix(m, n);
    vector<vector<int>> B = generateRandomMatrix(n, p);

    vector<int> blockSizes = {5, 8, 12, 16};  // Different block sizes to test

    cout << "Multiplying matrices of size " << m << "x" << n << " and " << n << "x" << p << endl;

    cout << "Testing different block sizes:\n";
    for (int blockSize : blockSizes) {
        double executionTime = measureExecutionTime(A, B, blockSize);
        cout << "Block size: " << blockSize  << ", Execution time: ";
        printf ("%lf\n",executionTime);
    } 

        
    return 0;
}