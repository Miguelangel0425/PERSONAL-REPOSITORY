#include "Fraccion.h"
#include <iostream>
#include <stdexcept>

Fraccion sumar(const Fraccion& f1, const Fraccion& f2);

int main() {
    while (!fraccionValida){
    try
    {
        int num1, den 1, num2, den 2;

        std::cout << "Ingrese el numerador de la primera fraccion: ";
        std::cin >> num1;
        std::cout << "Ingrese el denominador de la primera fraccion: ";
        std::cin >> den1;

        Fraccion fraccion1(num1, den1);

        std::cout << "Ingrese el numerador de la segunda fraccion: ";
        std::cin >> num2;
        std::cout << "Ingrese el denominador de la segunda fraccion: ";
        std::cin >> den2;

        Fraccion fraccion2(num2, den2);

        fraccionValida = true;

    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<< "Error: " << e.what() << ". Intentelo otra vez.\n" ;
    }  
    }

    Fraccion resultado = sumar(fraccion1, fraccion2);

    std::cout<< "la suma de las fraccionees es: "<< resultado.getNumerador() << "/" << resultado.getDenominador() << std::endl; 
}