#include <stdio.h>
#include <omp.h>

#define N 4

void matrizPorVector(int matriz[N][N], int vector[N], int resultado[N]) {
    int i,j;
    #pragma omp parallel for private(j)
    for (i = 0; i < N; i++) {
        resultado[i] = 0;
        for (j = 0; j < N; j++)
            resultado[i] += matriz[i][j] * vector[j];
    }
}

void main() {
    int matriz[N][N];
    int vector[N];
    int resultado[N];
    int c = 1;
    for (int i = 0; i < N; i++) {
        vector[i] = i+1;
        for (int j = 0; j < N; j++) {
            matriz[i][j] = c;
            c++;
        }
    }
    matrizPorVector(matriz, vector, resultado);
    printf("Resultado:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");
}
