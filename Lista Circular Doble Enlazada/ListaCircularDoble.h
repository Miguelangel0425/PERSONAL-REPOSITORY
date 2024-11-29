#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include <iostream>

class ListaCircularDoble {
private:
    class Nodo {
    public:
        int dato;
        Nodo* siguiente;
        Nodo* anterior;
        
        Nodo(int valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
    };
    
    Nodo* primero;
    Nodo* ultimo;

public:
    ListaCircularDoble();
    
    void Insertar(int dato);
    void Buscar(int dato);
    void Eliminar(int dato);
    void Mostrar();
};

#endif // LISTA_CIRCULAR_DOBLE_H