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

Nodo::Nodo(int _dato) {
    dato = _dato;
    siguiente = NULL;
    anterior = NULL;
}

void Nodo::setDato(int _dato) {
    dato = _dato;
}

void Nodo::setSiguiente(Nodo* _siguiente) {
    siguiente = _siguiente;
}

void Nodo::setAnterior(Nodo* _anterior) {
    anterior = _anterior;
}

int Nodo::getDato() {
    return dato;
}

Nodo* Nodo::getSiguiente() {
    return siguiente;
}

Nodo* Nodo::getAnterior() {
    return anterior;
}
