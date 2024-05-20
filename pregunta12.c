#include <mpi.h>
#include <stdio.h>
#include <math.h>

double formula_fibonacci(int n) {
    double sqrt5 = sqrt(5.0);
    double phi = (1.0 + sqrt5) / 2.0;
    double psi = (1.0 - sqrt5) / 2.0;
    return (pow(phi, n) - pow(psi, n)) / sqrt5;
}

int main(int argc, char** argv) {
    int rango, tamaño, n, i;
    double resultado;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);
    MPI_Comm_size(MPI_COMM_WORLD, &tamaño);

    if (rango == 0) { // Proceso Maestro
        printf("Ingrese el valor de n: ");
        scanf("%d", &n);

        for (i = 1; i < tamaño; i++) {
            MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        for (i = 1; i < tamaño; i++) {
            MPI_Recv(&resultado, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("El Proceso %d calculó Fibonacci(%d) = %f\n", i, n, resultado);
        }
    } else { // Procesos Esclavos
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        resultado = formula_fibonacci(n);
        MPI_Send(&resultado, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
