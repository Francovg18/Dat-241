#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rango, tamaño, N, local_N;
    int *datos_locales = NULL;
    int *datos_globales = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);
    MPI_Comm_size(MPI_COMM_WORLD, &tamaño);

    if (rango == 0) {
        printf("Introduce el número de términos (N): ");
        scanf("%d", &N);
        datos_globales = (int*)malloc(N * sizeof(int));
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_N = N / tamaño;
    if (rango < N % tamaño) {
        local_N++;
    }
    datos_locales = (int*)malloc(local_N * sizeof(int));

    int inicio = rango * (N / tamaño) + (rango < N % tamaño ? rango : N % tamaño);
    for (int i = 0; i < local_N; i++) {
        datos_locales[i] = 2 * (inicio + i + 1);
    }

    int *cuentas_recepcion = NULL;
    int *desplazamientos = NULL;

    if (rango == 0) {
        cuentas_recepcion = (int*)malloc(tamaño * sizeof(int));
        desplazamientos = (int*)malloc(tamaño * sizeof(int));

        int offset = 0;
        for (int i = 0; i < tamaño; i++) {
            cuentas_recepcion[i] = N / tamaño;
            if (i < N % tamaño) {
                cuentas_recepcion[i]++;
            }
            desplazamientos[i] = offset;
            offset += cuentas_recepcion[i];
        }
    }

    MPI_Gatherv(datos_locales, local_N, MPI_INT, datos_globales, cuentas_recepcion, desplazamientos, MPI_INT, 0, MPI_COMM_WORLD);

    // Imprimir
    if (rango == 0) {
        printf("Serie generada:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", datos_globales[i]);
        }
        printf("\n");

        // Liberar los arreglos relacionados con los datos globales
        free(datos_globales);
        free(cuentas_recepcion);
        free(desplazamientos);
    }

    // Liberar el arreglo de datos locales
    free(datos_locales);

    MPI_Finalize();

    return 0;
}
