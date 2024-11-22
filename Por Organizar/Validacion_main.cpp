/***********************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                  *
 * Proposito:                      Validaciones con casting            *
 * Autor:                          Miguel Caiza                        *
 * Fecha de creacion:              06/10/2024                          *
 * Fecha de modificacion:          07/11/2024                          *
 * Materia:                        Estructura de datos                 *
 * NRC :                           1978                                *
 ***********************************************************************/

#include "Validacion.h"
#include <iostream>


    int main(){

        Validacion entero;

        int numero1 = entero.ingresar("Ingrese un numero entero: ");
        std::cout  << std::endl;
        int numero2 = entero.ingresar("Ingrese un numero entero: ");
        std::cout  << std::endl;
        std::cout << "La suma de los numeros es: " << (numero1 + numero2) << std::endl;

        Validacion flotante

        float numero3 = flotante.ingresar("Ingrese un numero flotante: ");
        std::cout  << std::endl;
        float numero4 = flotante.ingresar("Ingrese un numero flotante: ");
        std::cout  << std::endl;
        std::cout << "La suma de los numeros es: " << (numero3 + numero4) << std::endl;

        Validacion caracter
        ;
        char letra1 = caracter.ingresar("Ingrese una letra: ");
        std::cout  << std::endl;

        Validacion string;

        std::string palabra = string.ingresar("Ingrese una palabra: ");
        std::cout  << std::endl;

        Validacion double;
        
        double numero5 = doble.ingresar("Ingrese un numero doble: ");
        std::cout  << std::endl;

    }