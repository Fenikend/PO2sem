#include <iostream>
#include <cmath>
#include <mpi.h>

using namespace std;

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

double integrate(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    return sum * h;
}

int main(int argc, char** argv) {
    int rank, size;
    int n = 10000000000; 
    double a = 0.0, b = 1.0; 
    double h = (b - a) / n;
    double sum = 0.0, local_sum = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Розрахунок частини суми на кожному процесі
    int local_n = n / size;
    double local_a = a + rank * local_n * h;
    double local_b = local_a + local_n * h;
    local_sum = integrate(local_a, local_b, local_n);

    // Збір частин суми на процесі 0
    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Обчислення числа пі
        double pi = sum;
        cout << "Pi = " << pi << endl;
    }

    MPI_Finalize();
    return 0;
}