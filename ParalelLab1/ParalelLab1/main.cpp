
#include <iostream>
#include <omp.h>
#include <typeinfo>

int main(int argc, char** argv)
{


    for (int j = 0;j < 10;j++) {
        omp_set_num_threads(j+1);
        double total_Sum = 0;

        double delta;
        const int exponent = 10;
        float start;
        float end;
        start = omp_get_wtime();
#pragma omp parallel shared(total_Sum,delta)
        {
            double Xi;
            double Fx;
            Xi = 0 + (omp_get_thread_num() * 0.1);
            //Xi = pow(0.1, omp_get_thread_num());
            delta = pow(10, -exponent);
            Fx = 0;
            long long int k = omp_get_thread_num() * pow(10, exponent - 1);
            long long int b = (omp_get_thread_num() + 1) * pow(10, exponent - 1);

            for (long long int i = k;i < b;i++)
            {



                Fx += 4 / (1 + Xi * Xi);

                Xi += delta;



            }

#pragma omp critical
            {
                Fx *= delta;
                //printf("Fx:%e,Xi:%e\n", Fx,Xi);
                total_Sum += Fx;

            }
        }
        end = omp_get_wtime();
        float elapsedTime = end - start;
        float performance = omp_get_num_threads() / (elapsedTime * pow(10, -9));
        printf("n:%d; Elapsed time:%f, total_Sum:%e, performance:%f\n", j+1,end - start, total_Sum, performance);

    }
    return 0;
}
/*
int partial_Sum, total_Sum;

#pragma omp parallel private(partial_Sum) shared(total_Sum)
{
    partial_Sum = 0;
    total_Sum = 0;
    #pragma omp for
        for (int i = 0; i <=1000; i++)
        {
            partial_Sum += i;
        }
    #pragma omp critical
        {
            total_Sum += partial_Sum;
        }
}
printf("TotalSum:%d\n", total_Sum);
return 0;
*/

//printf("Hello", omp_get_thread_num());
//std::cout << omp_get_thread_num();
//std::cout << omp_get_num_threads();



