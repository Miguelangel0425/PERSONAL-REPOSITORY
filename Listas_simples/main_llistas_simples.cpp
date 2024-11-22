/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Josue Chango, Adonny Calero, Eduardo altamirano     *
 * Fecha de creacion:              18/11/2024                                          *
 * Fecha de modificacion:          18/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/
#include "Lista_Simple.cpp"
#include "Nodo.cpp"
#include <iostream>
#include <stdlib.h>
#include "Validaciones.cpp"
//#include <windows.h>
using namespace std;


bool esEntero(string);

int main() {
    Lista_Simple<int>* lista_entero = new Lista_Simple<int>();
    Lista_Simple<float>* lista_flotante = new Lista_Simple<float>();
    Lista_Simple<double>* lista_doble = new Lista_Simple<double>();
    Lista_Simple<std::string>* lista_string = new Lista_Simple<std::string>();
    Lista_Simple<char>* lista_letras = new Lista_Simple<char>();

    int opcion, dato_entero;
    float dato_flotante;
    double dato_doble;
    std::string dato_string;
    char dato_char;

    Validaciones<int> ingresar_entero;
    Validaciones<float> ingresar_flotante;
    Validaciones<double> ingresar_doble;
    Validaciones<std::string> ingresar_string;
    Validaciones<char> ingresar_letra;

    /*HINSTANCE hDLL = LoadLibrary("ValidDll.dll");
    if (!hDLL) {
        std::cerr << "No se pudo cargar la DLL.\n";
        return 1;
    }*/


   do {
        system("cls");
        cout << "***********Listas Simples***********" << endl;
        cout << "1. Lista de enteros" << endl;
        cout << "2. lista de flotantes" << endl;
        cout << "3. lista de dobles" << endl;
        cout << "4. lista de strings" << endl;
        cout << "5. lista de letras" << endl;
        cout << "6. salir" << endl;
        opcion = ingresar_entero.ingresar("Opcion: ","entero");
        cout << endl;
        switch (opcion) {
        case 1:
            do {
                system("cls");
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a insertar: ", "entero");
                    cout << endl;
                    lista_entero->Insertar_cabeza(dato_entero);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a buscar: ", "entero");
                    cout << endl;
                    lista_entero->Buscar(dato_entero);
                    system("pause");
                    break;
                case 3:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a eliminar: ", "entero");
                    cout << endl;
                    lista_entero->Eliminar(dato_entero);
                    system("pause");
                    break;
                case 4:
                    lista_entero->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            break;
        case 2:
            do {
                system("cls");
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a insertar: ", "flotante");
                    cout << endl;
                    lista_flotante->Insertar_cabeza(dato_flotante);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a buscar: ", "flotante");
                    cout << endl;
                    lista_flotante->Buscar(dato_flotante);
                    system("pause");
                    break;
                case 3:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a eliminar: ", "flotante");
                    cout << endl;
                    lista_flotante->Eliminar(dato_flotante);
                    system("pause");
                    break;
                case 4:
                    lista_flotante->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            break;
        case 3:
            do {
                system("cls");
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a insertar: ", "double");
                    cout << endl;
                    lista_doble->Insertar_cabeza(dato_doble);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a buscar: ", "double");
                    cout << endl;
                    lista_doble->Buscar(dato_doble);
                    system("pause");
                    break;
                case 3:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a eliminar: ", "double");
                    cout << endl;
                    lista_doble->Eliminar(dato_doble);
                    system("pause");
                    break;
                case 4:
                    lista_doble->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            break;
        case 4:
            do {
                system("cls");
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_string = ingresar_string.ingresar("ingrese el dato a insertar: ", "string");
                    cout << endl;
                    lista_string->Insertar_cabeza(dato_string);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_string = ingresar_string.ingresar("ingrese el dato a buscar: ", "string");
                    cout << endl;
                    lista_string->Buscar(dato_string);
                    system("pause");
                    break;
                case 3:
                    dato_string = ingresar_string.ingresar("ingrese el dato a eliminar: ", "string");
                    cout << endl;
                    lista_string->Eliminar(dato_string);
                    system("pause");
                    break;
                case 4:
                    lista_string->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            break;
        case 5:
            do {
                system("cls");
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a insertar: ", "char");
                    cout << endl;
                    lista_letras->Insertar_cabeza(dato_char);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a buscar: ", "char");
                    cout << endl;
                    lista_letras->Buscar(dato_char);
                    system("pause");
                    break;
                case 3:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a eliminar: ", "char");
                    cout << endl;
                    lista_letras->Eliminar(dato_char);
                    system("pause");
                    break;
                case 4:
                    lista_letras->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            break;
        case 6:
            cout << "Gracias por visitarnos" << endl;
            system("pause");
            break;
        default:
            cout << "Opcion no valida, intente de nuevo" << endl;
            system("pause");
            break;
        }
    } while (opcion != 6);

    
    return 0;
}
