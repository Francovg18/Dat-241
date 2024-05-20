#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;
    #pragma omp parallel
    {
        num_threads = omp_get_num_threads();
        //printf("Hola Mundo desde el hilo %d de %d\n", omp_get_thread_num(), num_threads);
        printf("hola mundo\n");
    }
    return 0;
}