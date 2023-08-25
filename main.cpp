#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
int MAX = 10;

class RNG{
public:
    RNG() : gen(random_device()()) {}

    double getRandom(){
        uniform_real_distribution<double> dis(0,100.0);
        double random = dis(gen);
        return random;
    }
private:
    mt19937 gen;
};

int main() {

    //double A[MAX][MAX], x[MAX], y[MAX];
    //vector<vector<double>> A;
    double A[MAX][MAX];
    vector<double> x(MAX);
    vector<double> y(MAX);
    RNG rng_;

    /* Initialize A and x, assign y = 0 */
    for(int i=0; i<MAX; i++){
        x[i] = rng_.getRandom();
    }

    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            A[i][j] = rng_.getRandom();
        }
    }

    fill(y.begin(), y.end(), 0.0);
    cout << "data inicializada" << endl;

    /* First pair of loops */
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    auto end = chrono::steady_clock::now();

    cout << "El primer loop duro:" << endl;
    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;

    /* Assign y = 0 */
    fill(y.begin(), y.end(), 0.0);

    /* Second pair of loops */
    start = chrono::steady_clock::now();
    for (int j = 0; j < MAX; j++){
        for (int i = 0; i < MAX; i++){
            y[i] += A[i][j] * x[j];
        }
    }
    end = chrono::steady_clock::now();
    cout << "El segundo loop duro:" << endl;
    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;
}
