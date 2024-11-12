/***********************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                  *
 * Proposito:                      Validaciones con casting            *
 * Autor:                          Miguel Caiza                        *
 * Fecha de creacion:              06/10/2024                          *
 * Fecha de modificacion:          07/11/2024                          *
 * Materia:                        Estructura de datos                 *
 * NRC :                           1978                                *
 ***********************************************************************/

#ifndef Validacion_H
#define Validacion_H

#include <iostream> 
#include <conio.h>  
#include <string>
#include <stdlib.h>

template <typename T>

class Validacion{

    public:
        T ingresar(const char *msj);

};

//template enteros//
template <>
int Validacion<int>::ingresar(const char *msj);

//template floats//

template <>
float Validacion<float>::ingresar(const char *msj);

//template strings//

template <>
std::string Validacion<std::string>::ingresar(const char *msj);

//template char// 

template <>
char Validacion<char>::ingresar(const char *msj);

//template double//

template <>
double Validacion<double>::ingresar(const char *msj);

#endif //Validacion_H