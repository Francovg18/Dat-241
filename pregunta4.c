//4. Realizar en OPENMP la multiplicación de una matriz NxN, con un vector de dimensión N.
//gcc -fopenmp pregunta4.c -o pregunta4
#include <stdio.h>
#include <omp.h>

#define N 4

// Función multiplicar matriz
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
    //int N;
    //printf("Ingrese el valor de N");
    //scanf("%d", &N);
   
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

/*
printf("Ingrese los elementos de la matriz (%d x %d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

printf("Ingrese los elementos del vector (%d elementos):\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &vector[i]);
    }

int matriz[N][N] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};
    int vector[N] = {1, 2, 3, 4};
*/