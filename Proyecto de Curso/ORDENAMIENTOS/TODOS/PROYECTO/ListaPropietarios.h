#pragma once
#include <iostream>
#include <vector>
#include "Propietario.h"

using namespace std;

class ListaPropietarios
{
private:
    vector<Propietario> propietarios;

public:
    void agregarPropietario(const Propietario &propietario);
    Propietario* buscarPropietarioPorCedula(const string &cedula);
    void mostrarPropietarios() const;
    bool estaVacia() const;
    void cargarArchivo(const string &archivo); 
    void guardarArchivo(const string &archivo) const; 

    
};