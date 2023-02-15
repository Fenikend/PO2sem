// ParalelLab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
# include <stdio.h>
#include <omp.h>
#include <math.h> 


int monteCarlo(int threads) {
    omp_set_num_threads(threads);
    int seed=2;
    int const pointNum = 1E8;
    float* X=new float[pointNum];
    float* Y= new float[pointNum];
    float* points= new float[pointNum];
    int totalPoints;
    int threadPoint;
    
#pragma omp parallel private (threadPoint)  shared(totalPoints)
    {   totalPoints = 0;
        threadPoint=0;
        seed = omp_get_thread_num()+2;
        srand(seed);
#pragma omp for
    for (int i = 0;i < pointNum;i++) {
        X[i] = (float)rand() / RAND_MAX;
        Y[i] = (float)rand() / RAND_MAX;

        points[i] = sqrt(pow(X[i], 2) + pow(Y[i], 2));

        if (points[i] <= 1) {
            threadPoint++;
        }

    }
#pragma omp critical
    {
    totalPoints += threadPoint;
    }
    }

    float result = 4 * float(totalPoints)/ float(pointNum);
    printf("result: %f\n", result);
    return 0;
}

int main()
{
    std::cout << "Hello World!\n";
    monteCarlo(4);
}