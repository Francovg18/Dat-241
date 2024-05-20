//8. Genere la serie 2, 4, 6, 8, 10, 12, 14, 16, 18… en M
//vectores(procesadores) para N términos con OPENMP
//gcc -fopenmp pregunta8.c -o pregunta8
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void generar_serie(int *serie, int inicio, int fin) {
    for (int i = inicio; i < fin; i++) {
        serie[i] = 2 * (i + 1);
    }
}

int main() {
    int N, M;
    printf("Introduce el número de términos en la serie: ");
    scanf("%d", &N);

    // Hilos nros
    printf("Introduce el número de procesadores (hilos): ");
    scanf("%d", &M);

    int *serie = (int *)malloc(N * sizeof(int));

    if (serie == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    // Dividir el trabajo entre los hilos -> OpenMP
    #pragma omp parallel num_threads(M)
    {
        int id_hilo = omp_get_thread_num();
        int num_hilos = omp_get_num_threads();

        int terminos_por_hilo = N / num_hilos;
        int inicio = id_hilo * terminos_por_hilo;
        int fin = (id_hilo == num_hilos - 1) ? N : inicio + terminos_por_hilo;

        generar_serie(serie, inicio, fin);
    }

    // Imprimir
    printf("Serie generada: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", serie[i]);
    }
    printf("\n");

    free(serie);

    return 0;
}
