#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;
    #pragma omp parallel
    {
        num_threads = omp_get_num_threads();
        printf("hola mundo\n");
    }
    return 0;
}
