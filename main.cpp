#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " MAX size e.g. 100" << std::endl;
        return EXIT_FAILURE;
    }
    int MAX = atoi(argv[1]);
    cout << "MAX: " << MAX << endl;

    //double A[MAX][MAX], x[MAX], y[MAX];
    double ** A = new double*[MAX];
    A[0] = new double[MAX*MAX];
    for(int i=1; i<MAX; i++){
        A[i] = A[i-1] + MAX;
    }

    double * x = new double(MAX);
    double * y = new double(MAX);
    
    // random
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(0.0, 10.0);

    /* Initialize A and x, assign y = 0 */
    for(int i=0; i<MAX; i++){
        //x[i] = rng_.getRandom();
        x[i] = distr(eng);
        //x.push_back(distr(eng));
    }

    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            A[i][j] = distr(eng);
            //A[i].push_back(distr(eng));
        }
    }

    // fill(y.begin(), y.end(), 0.0);
    for(int i=0; i<MAX; i++){
        y[i] = 0.0;
    }
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
    //fill(y.begin(), y.end(), 0.0);
    for(int i=0; i<MAX; i++){
        y[i] = 0.0;
    }

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

    return 0;
}
