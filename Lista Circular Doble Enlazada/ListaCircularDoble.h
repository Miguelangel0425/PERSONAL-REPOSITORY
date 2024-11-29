#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H
#include "Nodo.h"
#include <iostream>

template <typename T>
class ListaCircularDoble {
    private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    public:
    ListaCircularDoble();
    ~ListaCircularDoble();
    void agregarAlFinal(T dato);
    void agregarAlInicio(T dato);
    void eliminar(T dato);
    void eliminarPosicion(int posicion);
    void mostrar();
};

#endif // LISTA_CIRCULAR_DOBLE_H