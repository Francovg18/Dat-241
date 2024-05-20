//6.-En MPI realizar el cálculo de PI
//mpicc pregunta6.c -o pregunta6 -lm

#include <mpi.h>
#include <stdio.h>
#include <math.h>

double calcular_pi(int inicio, int fin) {
    double suma = 0.0;
    for (int i = inicio; i < fin; i++) {
        suma += 1.0 / (i * i);
    }
    return suma;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rango, tamaño;
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);
    MPI_Comm_size(MPI_COMM_WORLD, &tamaño);

    int limite = 1000;
    int n = limite / tamaño;
    int inicio = rango * n + 1;
    int fin = (rango + 1) * n + 1;

    double suma_local = calcular_pi(inicio, fin);

    double suma_total = 0.0;
    MPI_Reduce(&suma_local, &suma_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rango == 0) {
        double pi = sqrt(6 * suma_total);
        printf("Valor calculado de pi: %.15f\n", pi);
    }

    MPI_Finalize();
    return 0;
}