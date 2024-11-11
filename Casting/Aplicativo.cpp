#include "Validacion.h"
#include <iostream>


    int main(){

        Validacion entero;

        int numero1 = entero.ingresar("Ingrese un numero entero: ");
        std::cout  << std::endl;
        int numero2 = entero.ingresar("Ingrese un numero entero: ");
        std::cout  << std::endl;
        std::cout << "La suma de los numeros es: " << (numero1 + numero2) << std::endl;

        Validacion flotante;

        float numero3 = flotante.ingresar("Ingrese un numero flotante: ");
        std::cout  << std::endl;
        float numero4 = flotante.ingresar("Ingrese un numero flotante: ");
        std::cout  << std::endl;
        std::cout << "La suma de los numeros es: " << (numero3 + numero4) << std::endl;

        Validacion caracter
        ;
        char letra1 = caracter.ingresar("Ingrese una letra: ");
        std::cout  << std::endl;

        Validacion cadena;

        std::string palabra = cadena.ingresar("Ingrese una palabra: ");
        std::cout  << std::endl;

        Validaccion doble;
        
        double numero5 = doble.ingresar("Ingrese un numero doble: ");
        std::cout  << std::endl;

    }