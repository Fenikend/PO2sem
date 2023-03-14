#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define N 2000

int main()
{
    for (int thr = 1; thr <= 4; thr++) {
        omp_set_num_threads(thr);
        double tStart = omp_get_wtime();
        int** A, ** B, ** C;

        A = new int* [N];
        B = new int* [N];
        C = new int* [N];

        for (int i = 0; i < N; i++) {
            A[i] = new int[N];
            B[i] = new int[N];
            C[i] = new int[N];
        }

        srand(time(0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = rand() % 100;
                B[i][j] = rand() % 100;
                C[i][j] = 0;
            }
        }
        double tEnd = omp_get_wtime();
        double tSeq = tEnd - tStart;
        double tStartPar = omp_get_wtime();
#pragma omp parallel for
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                    
                }
               
            }
            //if (i%100==0){ std::cout << i; }
           
        }
        double tEndPar = omp_get_wtime();
        double tPar = tEndPar - tStartPar;
        double totalOperations = static_cast<double>(N) * N * N;
        double parallelFraction = totalOperations / (tPar + tSeq);
        double coeffProductivity = tSeq / (tPar + tSeq);
        double speedupCoeff = tSeq / tPar;
       
        printf("numThreads:%d, Parallel Fraction: %e, Coefficient of Productivity: %f, Speedup Coefficient: %f, Sequential Time: %f, Parallel Time: %f\n", thr,parallelFraction, coeffProductivity, speedupCoeff, tSeq, tPar);

        for (int i = 0; i < N; i++) {
            delete[] A[i];
            delete[] B[i];
            delete[] C[i];
        }
        delete[] A;
        delete[] B;
        delete[] C;
    }
}
