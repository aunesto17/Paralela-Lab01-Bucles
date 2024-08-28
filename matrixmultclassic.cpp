#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// Function to multiply two matrices (O(mnp))
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();

    vector<vector<int>> C(m, vector<int>(p, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
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

    cout << "m: " << m << endl;
    cout << "n: " << n << endl;
    cout << "p: " << p << endl;

    // random
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<> distr(0, 100);

    // instance and fill matrices
    vector<vector<int>> A(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = distr(eng);
        }
    }

    vector<vector<int>> B(n, vector<int>(p, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            B[i][j] = distr(eng);
        }
    }

    // cout << "Matrix A:" << endl;
    // printMatrix(A);

    cout << "\nMatrix B:" << endl;
    // printMatrix(B);

    auto start = chrono::steady_clock::now();
    vector<vector<int>> C = multiplyMatrices(A, B);
    auto end = chrono::steady_clock::now();

    double cpu_time_used = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    // auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // cout << "Time taken: " << cpu_time_used << " ns" << endl;
    printf ("%lf\n",cpu_time_used); 

    cout << "\nResultant Matrix C = A * B:" << endl;
    //printMatrix(C);

    return 0;
}