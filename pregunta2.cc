#include <iostream>

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
    // Verificar si num2 es igual a 0
    if (*num2 == 0) {
        std::cout << "No se puede dividir entre 0." << std::endl;
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
   
    std::cout << "Ingrese el primer número: ";
    std::cin >> num1;
    std::cout << "Ingrese el segundo número: ";
    std::cin >> num2;

    std::cout << "Suma: " << suma(&num1, &num2) << std::endl;
    std::cout << "Resta: " << resta(&num1, &num2) << std::endl;
    std::cout << "Multiplicacion: " << multiplicacion(&num1, &num2) << std::endl;
    std::cout << "Division: " << division(&num1, &num2) << std::endl;

    return 0;
}
