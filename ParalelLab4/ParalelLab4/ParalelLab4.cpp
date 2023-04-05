#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <string>

#define N 4000

int main()
{
   
    //const char* opType = { };
    for (int thr = 1; thr <= 4; thr++) {
        omp_set_num_threads(thr);
        double tStart = omp_get_wtime();
        int** A, ** B, ** res1,** res2,**V;
        
        A = new int* [N];
        B = new int* [N];
        res1 = new int* [N];
        res2= new int* [N];
        V= new int* [N];
        V[0] = new int [N];
        res1[0] = new int[N];
        res2[0] = new int[N];
        for (int i = 0; i < N; i++) {
            A[i] = new int[N];
            B[i] = new int[N];
            
         
        }
        srand(time(0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = rand() % 100;
                if (i > j) {
                    B[i][j] = 0;
                }
                else {
                    B[i][j] = rand() % 100;
                }
                if (i == 0) {
                    V[0][j] = rand() % 100;
                    res1[0][j] = 0;
                    res2[0][j] = 0;
                }

                //std::cout << B[i][j]<<" ";
               
            }
            //std::cout << "\n";
        }
        double tEnd = omp_get_wtime();
        double tSeq = tEnd - tStart;
        double tStartPar = omp_get_wtime();

#pragma omp parallel for schedule(runtime)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                res1[0][j] += A[i][j] * V[0][j];
                res2[0][j] += B[i][j] * V[0][j];
                

            }
            //if (i%100==0){ std::cout << i; }
            
        }
        double tEndPar = omp_get_wtime();
        double tPar = tEndPar - tStartPar;
        double totalOperations = static_cast<double>(N) * N * N;
        double parallelFraction = totalOperations / (tPar + tSeq);
        double coeffProductivity = tSeq / (tPar + tSeq);
        double speedupCoeff = tSeq / tPar;
        
       printf("numThreads:%d, Parallel Fraction: %e, Coefficient of Productivity: %f, Speedup Coefficient: %f, Sequential Time: %f, Parallel Time: %f\n", thr, parallelFraction, coeffProductivity, speedupCoeff, tSeq, tPar);

        for (int i = 0; i < N; i++) {
            delete[] A[i];
            delete[] B[i];
        }
        delete[] A;
        delete[] B;
        delete[] res1[0];
        delete[] res2[0];
        delete[] res1;
        delete[] res2;
        delete[] V[0];
        delete[] V;
    }
}
