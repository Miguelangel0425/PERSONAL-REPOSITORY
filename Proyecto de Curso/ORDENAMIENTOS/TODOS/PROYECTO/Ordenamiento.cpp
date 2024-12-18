#include <iostream>
#include <vector>
#include <algorithm>
#include "Coche.h"
#include <functional>

template <typename T, typename Comparator>
int partition(std::vector<T>& lista, int low, int high, Comparator comp) {
    T pivot = lista[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (comp(lista[j], pivot)) {
            i++;
            std::swap(lista[i], lista[j]);
        }
    }
    std::swap(lista[i + 1], lista[high]);
    return i + 1;
}

template <typename T, typename Comparator>
void quickSort(std::vector<T>& lista, int low, int high, Comparator comp) {
    if (low < high) {
        int pi = partition(lista, low, high, comp);
        quickSort(lista, low, pi - 1, comp);
        quickSort(lista, pi + 1, high, comp);
    }
}

template <typename T, typename Comparator>
void bubbleSort(std::vector <T>&lista,Comparator comp){
    int n = lista.size();
    bool swapped; // Bandera para saber si se realizó un intercambio
    for (int i = 0; i < n - 1; i++) {
        swapped = false;// Inicializar la bandera en falso
        
        for (int j = 0; j < n - i - 1; j++) {
            if (comp(lista[j], lista[j + 1])) {
                std::swap(lista[j], lista[j + 1]);
                swapped = true;//se realizó un intercambio
            }
        }
        //Si no se realizan cambios, la lista ya esta en orden
        //terminar el ciclo
        if (!swapped) {
            break;
        }
    }
}

template <typename T, typename Comparator>
void ordenarLista(ListaCircularDoble<T>& lista, Comparator comp) {
    std::vector<T> elementos;
    
    Nodo<T>* aux = lista.getPrimero();
    do {   
        elementos.push_back(aux->getDato());
        aux = aux->getSiguiente();
    } while (aux != lista.getPrimero());

    quickSort(elementos, 0, elementos.size() - 1, comp);

    aux = lista.getPrimero();
    int index = 0;
    do {
        aux->setDato(elementos[index++]);
        aux = aux->getSiguiente();
    } while (aux != lista.getPrimero());

    lista.mostrar(lista.getPrimero());
}

template <typename T, typename Comparator>
void ordenarListaBubbleSort(ListaCircularDoble<T>& lista,Comparator comp){
    std::vector<T> elementos;

    Nodo<T>* aux = lista.getPrimero();
    do{                     // Extraer los elementos de la lista circular doble
        elementos.push_back(aux->getDato());
        aux= aux->getSiguiente();
    }while (aux != lista.getPrimero());

    bubbleSort(elementos,comp);// Ordenar los elementos

    aux=lista.getPrimero();
    int index=0;// Volver a insertar los elementos ordenados en la lista circular doble
    do{
        aux->setDato(elementos[index++]);
        aux=aux->getSiguiente();
    }while (aux != lista.getPrimero());

    lista.mostrar(lista.getPrimero());
}

template <typename T>
void ordenarListaBucket(ListaCircularDoble<T>& lista, std::function<std::string(const T&)> getKey) {
    std::vector<T> elementos;

    // Extraer los elementos de la lista circular doble
    Nodo<T>* aux = lista.getPrimero();
    if (aux == nullptr) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    do {
        elementos.push_back(aux->getDato());
        aux = aux->getSiguiente();
    } while (aux != lista.getPrimero());

    
    const int bucketCount = 256; 
    std::vector<std::vector<T>> buckets(bucketCount);

    // Distribuir los elementos en los buckets
    for (const auto& item : elementos) {
        std::string key = getKey(item);
        if (!key.empty()) {
            char firstChar = tolower(key[0]); // Usar el primer carácter de la clave
            int bucketIndex = static_cast<int>(firstChar);
            buckets[bucketIndex].push_back(item);
        }
    }

    // Limpiar el vector de elementos
    elementos.clear();

    // Ordenar cada bucket y volver a insertar en el vector de elementos
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end(), [&getKey](const T& a, const T& b) {
            return getKey(a) < getKey(b); // Usar la clave para ordenar
        });
        elementos.insert(elementos.end(), bucket.begin(), bucket.end());
    }

    // Volver a insertar los elementos ordenados en la lista circular doble
    aux = lista.getPrimero();
    int index = 0;
    do {
        aux->setDato(elementos[index++]);
        aux = aux->getSiguiente();
    } while (aux != lista.getPrimero());

    // Mostrar la lista ordenada
    lista.mostrar(lista.getPrimero());
}