/*************************
 * UFA-ESPE
 * ALUMNOS:  Leonardo Obando, William Leon
 * FECHA CREACION: Miercoles, 21 de noviembre de 2022
 * FECHA MODIFICACION: Miercoles, 23 de noviembre de 2022
 * Enunciado del problema: Crear los métodos Insertar, Buscar
 y Eliminar elementos de una lista Simple, Doble y Circular
 * Nivel: TERCERO     NRC: 7999
 *************************/
#pragma once
#include "Nodo.h"

using namespace std;

class ListaCircular {
private:
    Nodo* primero;
    Nodo* ultimo;
public:
    ListaCircular();
    void Insertar(int);
    void Buscar(int);
    void Eliminar(int);
    void Mostrar();
};



