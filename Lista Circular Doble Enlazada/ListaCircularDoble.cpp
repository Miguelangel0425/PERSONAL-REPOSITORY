#include "ListaCircularDoble.h"

using namespace std;


template <typename T>
ListaCircularDoble<T>::ListaCircularDoble() {
    primero = nullptr;
    ultimo = nullptr;
}

// Destructor
template <typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    while (primero != nullptr) {
        eliminar(primero->dato);
    }
}

// Agregar al final
template <typename T>
void ListaCircularDoble<T>::agregarAlFinal(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    if (primero == nullptr) { // Lista vacía
        primero = nuevoNodo;
        ultimo = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
    } else {
        nuevoNodo->anterior = ultimo;
        nuevoNodo->siguiente = primero;
        ultimo->siguiente = nuevoNodo;
        primero->anterior = nuevoNodo;
        ultimo = nuevoNodo;
    }
}

// Agregar al inicio
template <typename T>
void ListaCircularDoble<T>::agregarAlInicio(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    if (primero == nullptr) { // Lista vacía
        primero = nuevoNodo;
        ultimo = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
    } else {
        nuevoNodo->siguiente = primero;
        nuevoNodo->anterior = ultimo;
        ultimo->siguiente = nuevoNodo;
        primero->anterior = nuevoNodo;
        primero = nuevoNodo;
    }
}

// Eliminar un elemento
template <typename T>
void ListaCircularDoble<T>::eliminar(T dato) {
    if (primero == nullptr) return; // Lista vacía

    Nodo<T>* actual = primero;
    do {
        if (actual->dato == dato) {
            if (actual == primero && actual == ultimo) { // Solo un nodo
                delete actual;
                primero = nullptr;
                ultimo = nullptr;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                if (actual == primero) {
                    primero = actual->siguiente;
                }
                if (actual == ultimo) {
                    ultimo = actual->anterior;
                }
                delete actual;
            }
            return; // Salir tras eliminar el nodo
        }
        actual = actual->siguiente;
    } while (actual != primero);
}

// Eliminar por posición
template <typename T>
void ListaCircularDoble<T>::eliminarPosicion(int posicion) {
    if (primero == nullptr) return; // Lista vacía

    Nodo<T>* actual = primero;
    int index = 0;

    do {
        if (index == posicion) {
            if (actual == primero && actual == ultimo) { // Solo un nodo
                delete actual;
                primero = nullptr;
                ultimo = nullptr;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                if (actual == primero) {
                    primero = actual->siguiente;
                }
                if (actual == ultimo) {
                    ultimo = actual->anterior;
                }
                delete actual;
            }
            return; // Salir tras eliminar el nodo
        }
        actual = actual->siguiente;
        index++;
    } while (actual != primero);
}

// Mostrar la lista
template <typename T>
void ListaCircularDoble<T>::mostrar() {
    if (primero == nullptr) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    Nodo<T>* actual = primero;
    do {
        std::cout << actual->dato << " ";
        actual = actual->siguiente;
    } while (actual != primero);
    std::cout << std::endl;
}