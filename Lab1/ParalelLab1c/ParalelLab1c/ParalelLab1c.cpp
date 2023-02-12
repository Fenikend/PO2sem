// ParalelLab1c.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <omp.h>



int threadHello(int threads) 
{
    omp_set_num_threads(threads);
#pragma omp parallel 
    printf("Hello from process:%d\n", omp_get_thread_num());
    return 0;
}
int countToH(int threads) {
    omp_set_num_threads(threads);
    int partial_sum, total_Sum;
#pragma omp parallel private(partial_sum) shared(total_Sum)
    {
        partial_sum = 0;
        total_Sum = 0;
    #pragma omp for
        for (int i = 1;i <= 1000;i++) {
            partial_sum += i;
        }
    #pragma omp critical
        total_Sum += partial_sum;
    }

    printf("Total sum : %d\n", total_Sum);
    return 0;
}

int main(int argc, char** argv)
{
    threadHello(4);
    countToH(4);
}
