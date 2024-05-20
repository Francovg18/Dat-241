//3. En openMP realice la multiplicación y división en base a sumas y restas.
// gcc -fopenmp pregunta3.c -o pregunta3
#include <stdio.h>
#include <omp.h>

int multiplicacion(int num1, int num2) {
    int resultado = 0;
    #pragma omp parallel for reduction(+:resultado)
    for (int i = 0; i < num2; ++i) {
        resultado += num1;
    }
    return resultado;
}

int division(int num1, int num2) {
    int resultado = 0;
    while (num1 >= num2) {
        #pragma omp atomic
        resultado++;
        num1 -= num2;
    }
    return resultado;
}

int main() {
    int num1, num2;
   
    printf("Ingrese el primer número: ");
    scanf("%d", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%d", &num2);

    printf("Multiplicacion: %d\n", multiplicacion(num1, num2));
    printf("Division: %d\n", division(num1, num2));

    return 0;
}