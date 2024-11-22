/*************************
 * UFA-ESPE
 * ALUMNOS:  Leonardo Obando, William Leon
 * FECHA CREACION: Miercoles, 21 de noviembre de 2022
 * FECHA MODIFICACION: Miercoles, 23 de noviembre de 2022
 * Enunciado del problema: Crear los métodos Insertar, Buscar
 y Eliminar elementos de una lista Simple, Doble y Circular
 * Nivel: TERCERO     NRC: 7999
 *************************/
#include "Nodo.h"

using namespace std;

Nodo::Nodo(int dato) {
    this->dato = dato;
    this->siguiente = NULL;
}

void Nodo::setDato(int dato) {
    this->dato = dato;
}

int Nodo::getDato() {
    return this->dato;
}

void Nodo::setSiguiente(Nodo* siguiente) {
    this->siguiente = siguiente;
}

Nodo* Nodo::getSiguiente() {
    return this->siguiente;
}
