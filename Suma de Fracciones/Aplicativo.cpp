#include "Fraccion.h"
#include <iostream>
#include <stdexcept>

Fraccion sumar(const Fraccion& f1, const Fraccion& f2);

int main() {
    bool fraccionValida = false; 
    int num1, den1, num2, den2;
    Fraccion fraccion1(0, 1);
    Fraccion fraccion2(0, 1);

    while (!fraccionValida) {
        try {
            std::cout << "Ingrese el numerador de la primera fraccion: ";
            std::cin >> num1;
            std::cout << "Ingrese el denominador de la primera fraccion: ";
            std::cin >> den1;

            fraccion1 = Fraccion(num1, den1);

            std::cout << "Ingrese el numerador de la segunda fraccion: ";
            std::cin >> num2;
            std::cout << "Ingrese el denominador de la segunda fraccion: ";
            std::cin >> den2;

            fraccion2 = Fraccion(num2, den2);

            fraccionValida = true;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << ". Intentelo otra vez.\n";
        }
    }

    Fraccion resultado = sumar(fraccion1, fraccion2);
    std::cout << "La suma de las fracciones es: " 
              << resultado.getNumerador() << "/" 
              << resultado.getDenominador() << std::endl;

    return 0;
}