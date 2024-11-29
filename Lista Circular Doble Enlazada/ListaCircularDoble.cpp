#include "ListaCircularDoble.h"
#include <iostream>

ListaCircularDoble::ListaCircularDoble() : primero(nullptr), ultimo(nullptr) {}

void ListaCircularDoble::Insertar(int dato) {
    Nodo* nuevo = new Nodo(dato);
    
    if (primero == nullptr) {

        primero = nuevo;
        ultimo = nuevo;
        primero->siguiente = primero;
        primero->anterior = primero;
    } else {

        nuevo->anterior = ultimo;
        nuevo->siguiente = primero;
        ultimo->siguiente = nuevo;
        primero->anterior = nuevo;
        ultimo = nuevo;
    }
}

void ListaCircularDoble::Buscar(int dato) {
    if (primero == nullptr) {
        std::cout << "La lista está vacía" << std::endl;
        return;
    }
    
    Nodo* actual = primero;
    bool encontrado = false;
    
    do {
        if (actual->dato == dato) {
            std::cout << "El elemento " << dato << " ha sido encontrado en la lista" << std::endl;
            encontrado = true;
            break;
        }
        actual = actual->siguiente;
    } while (actual != primero);
    
    if (!encontrado) {
        std::cout << "El elemento " << dato << " no ha sido encontrado en la lista" << std::endl;
    }
}

void ListaCircularDoble::Eliminar(int dato) {
    if (primero == nullptr) {
        std::cout << "La lista está vacía" << std::endl;
        return;
    }
    
    Nodo* actual = primero;
    bool encontrado = false;
    
    do {
        if (actual->dato == dato) {

            if (primero == ultimo) {
                delete primero;
                primero = nullptr;
                ultimo = nullptr;
                encontrado = true;
                break;
            }
            

            if (actual == primero) {
                primero = actual->siguiente;
                ultimo->siguiente = primero;
                primero->anterior = ultimo;
            }

            else if (actual == ultimo) {
                ultimo = actual->anterior;
                primero->anterior = ultimo;
                ultimo->siguiente = primero;
            }

            else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            
            delete actual;
            encontrado = true;
            std::cout << "El elemento " << dato << " ha sido eliminado de la lista" << std::endl;
            break;
        }
        actual = actual->siguiente;
    } while (actual != primero);
    
    if (!encontrado) {
        std::cout << "El elemento " << dato << " no ha sido encontrado en la lista" << std::endl;
    }
}

void ListaCircularDoble::Mostrar() {
    if (primero == nullptr) {
        std::cout << "La lista está vacía" << std::endl;
        return;
    }
    
    Nodo* actual = primero;
    do {
        std::cout << actual->dato << " <-> ";
        actual = actual->siguiente;
    } while (actual != primero);
    
    std::cout << " (ciclo)" << std::endl;
}