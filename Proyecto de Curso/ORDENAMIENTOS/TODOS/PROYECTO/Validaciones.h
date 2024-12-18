#pragma once

#include <iostream>

using namespace std;

class Validaciones
{
public:
    
    string ingresarString(const string &msj);
    bool validarCedula(const string &cedula);
    bool validarCorreo(const string &correo);
    string ingresarCedula(const string &msj);
    string ingresarCorreo(const string &msj);
};

