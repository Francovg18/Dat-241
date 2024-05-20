#include <stdio.h>

float suma(float *num1, float *num2) {
    return *num1 + *num2;
}

float resta(float *num1, float *num2) {
    return *num1 - *num2;
}

float multiplicacion(float *num1, float *num2) {
    if (*num1 == 0 || *num2 == 0) {
        return 0;
    } else if (*num1 < 0 && *num2 < 0) {
        *num1 = -*num1;
        *num2 = -*num2;
    } else if (*num1 < 0 || *num2 < 0) {
        *num1 = (*num1 < 0) ? -*num1 : *num1;
        *num2 = (*num2 < 0) ? -*num2 : *num2;
    }

    float resultado = 0;
    for (int i = 0; i < *num2; ++i) {
        resultado += *num1;
    }
    return resultado;
}

float division(float *num1, float *num2) {
    if (*num2 == 0) {
        printf("No se puede dividir entre 0.\n");
        return 0;
    }

    if (*num1 < 0 && *num2 < 0) {
        *num1 = -*num1;
        *num2 = -*num2;
    } else if (*num1 < 0 || *num2 < 0) {
        *num1 = (*num1 < 0) ? -*num1 : *num1;
        *num2 = (*num2 < 0) ? -*num2 : *num2;
    }

    float resultado = 0;
    while (*num1 >= *num2) {
        resultado++;
        *num1 -= *num2;
    }
    return resultado;
}

int main() {
    float num1, num2;
   
    printf("Ingrese el primer número: ");
    scanf("%f", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%f", &num2);

    printf("Suma: %.2f\n", suma(&num1, &num2));
    printf("Resta: %.2f\n", resta(&num1, &num2));
    printf("Multiplicacion: %.2f\n", multiplicacion(&num1, &num2));
    printf("Division: %.2f\n", division(&num1, &num2));

    return 0;
}
