#pragma once

#include <iostream>
#include <string>
#include "Nodo.h"
#include "Lista.h"

using namespace std;

template <typename T>
class Placa
{
public:
    string ingresarPlaca(Nodo<T> *aux);

private:
    void convertirAMayusculas(string &placa);
};

#include "ValidacionPlaca.cpp"