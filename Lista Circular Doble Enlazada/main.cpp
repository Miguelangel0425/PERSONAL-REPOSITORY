#include "ListaCircularDoble.h"
#include "Validaciones.h"
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
void menuListaCircular() {
    ListaCircularDoble lista;
    Validaciones<T> validador;
    int opcion;
    T elemento;

    do {
        std::cout << "\n--- MENÚ LISTA CIRCULAR DOBLE ---\n";
        std::cout << "1. Insertar elemento\n";
        std::cout << "2. Buscar elemento\n";
        std::cout << "3. Eliminar elemento\n";
        std::cout << "4. Mostrar lista\n";
        std::cout << "5. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        
        opcion = validador.ingresar((char*)"Ingrese opción: ", (char*)"entero");

        switch (opcion) {
            case 1:
                elemento = validador.ingresar((char*)"Ingrese elemento a insertar: ", 
                    std::is_same<T, int>::value ? (char*)"entero" :
                    std::is_same<T, float>::value ? (char*)"flotante" :
                    std::is_same<T, double>::value ? (char*)"double" : (char*)"string");
                lista.Insertar(elemento);
                std::cout << "Elemento insertado correctamente.\n";
                break;
            
            case 2:
                elemento = validador.ingresar((char*)"Ingrese elemento a buscar: ", 
                    std::is_same<T, int>::value ? (char*)"entero" :
                    std::is_same<T, float>::value ? (char*)"flotante" :
                    std::is_same<T, double>::value ? (char*)"double" : (char*)"string");
                lista.Buscar(elemento);
                break;
            
            case 3:
                elemento = validador.ingresar((char*)"Ingrese elemento a eliminar: ", 
                    std::is_same<T, int>::value ? (char*)"entero" :
                    std::is_same<T, float>::value ? (char*)"flotante" :
                    std::is_same<T, double>::value ? (char*)"double" : (char*)"string");
                lista.Eliminar(elemento);
                break;
            
            case 4:
                std::cout << "Contenido de la lista: ";
                lista.Mostrar();
                break;
        }
    } while (opcion != 5);
}

int main() {
    Validaciones<int> validador;
    int opcion;

    do {
        std::cout << "\n--- MENÚ PRINCIPAL ---\n";
        std::cout << "1. Lista Circular de Enteros\n";
        std::cout << "2. Lista Circular de Flotantes\n";
        std::cout << "3. Lista Circular de Doubles\n";
        std::cout << "4. Lista Circular de Caracteres\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione un tipo de lista: ";
        
        opcion = validador.ingresar((char*)"Ingrese opción: ", (char*)"entero");

        switch (opcion) {
            case 1: menuListaCircular<int>(); break;
            case 2: menuListaCircular<float>(); break;
            case 3: menuListaCircular<double>(); break;
            case 4: menuListaCircular<char>(); break;
            case 5: std::cout << "Saliendo del programa...\n"; break;
            default: std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 5);

    return 0;
}