
#include <iostream>
#include <fstream>
#include <omp.h>
#include <typeinfo>
#include <string> 
int main(int argc, char** argv)
{
    int const num_of_threads = 4;
    for (int j = 0; j < num_of_threads; j++)
        {
        omp_set_num_threads(j + 1);
            double total_Sum = 0;
            double delta;
            const int exponent = 9;
            float start;
            float end;
            start = omp_get_wtime();
            long int k;
        long int b;
        double Xi;
        #pragma omp parallel private(k,b,Xi)shared(total_Sum,delta)
            {   float treadNum = (float)omp_get_thread_num();
                float numOfThreads = (float)omp_get_num_threads();
            
                double Fx;
                delta = pow(10, -exponent);
                Xi = 0+ (treadNum / numOfThreads)+delta;
                //Xi = pow(0.1, omp_get_thread_num());
                Fx = 0;
                k = treadNum/numOfThreads * pow(10, exponent - 1);
                b = ((treadNum + 1)/ numOfThreads) * pow(10, exponent -1 );
                
           
                for ( double i = k;i < b;i=i+0.1)
                {
                    Fx += 4 / (1 + Xi * Xi);
                    Xi += delta;
                }

            #pragma omp critical
                {
                    Fx *= (delta);
                    //printf("Fx:%e,Xi:%e\n", Fx,Xi);
                    total_Sum += Fx;
                }
            }
        end = omp_get_wtime();
        float elapsedTime = end - start;
        
        float performance = omp_get_num_threads() / elapsedTime * pow(10, -9);
        printf("Num of threads:%d,Elapsed time:%f, total_Sum:%f, performance:%e\n", j+1,end - start, total_Sum, performance);
        
    

        }
    
    return 0;
    }
   

   


