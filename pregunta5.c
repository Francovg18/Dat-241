#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4

void Imprimir(int matriz[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void multiplicacionMatriz(int matriz[N][N], int vector[N], int resultado[N], int rango) {
    int resultado_local[N] = {0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            resultado_local[i] += matriz[i][j] * vector[j];
        }
    }

    MPI_Gather(resultado_local, N, MPI_INT, resultado, N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rango == 0) {
        printf("Resultado:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", resultado[i]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    int rango, tamaño;
    int matriz[N][N] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};
    int vector[N] = {1, 2, 3, 4};
    int resultado[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);
    MPI_Comm_size(MPI_COMM_WORLD, &tamaño);

    if (tamaño != N) {
        if (rango == 0)
            printf("El número de procesos de MPI es diferente a la dimensión N.\n");
        MPI_Finalize();
        return 1;
    }

    multiplicacionMatriz(matriz, vector, resultado, rango);

    MPI_Finalize();
    return 0;
}
