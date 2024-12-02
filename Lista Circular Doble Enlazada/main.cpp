/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista doble enlazada                 *
 * Autor:                          Miguel Caiza                                        *
 * Fecha de creacion:              18/11/2024                                          *
 * Fecha de modificacion:          18/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "ListaCircularDoble.h"
#include "Validaciones.h"
#include "Nodo.h"

using namespace std;

bool esEntero(string);

int main() {
    ListaCircularDoble<int>* lista_entero = new ListaCircularDoble<int>();
    ListaCircularDoble<float>* lista_flotantes = new ListaCircularDoble<float>();
    ListaCircularDoble<double>* lista_doble = new ListaCircularDoble<double>();
    ListaCircularDoble<std::string>* lista_string = new ListaCircularDoble<std::string>();
    ListaCircularDoble<char>* lista_caracter = new ListaCircularDoble<char>();

    int opcion,dato_entero;
    float dato_flotante;
    double dato_doble;
    std::string dato_string;
    char dato_caracter;

    Validaciones<int> ingresar_entero;
    Validaciones<float> ingresar_flotante;
    Validaciones<double> ingresar_doble;
    Validaciones<std::string> ingresar_string;
    Validaciones<char> ingresar_caracter;
    
    do{
        system("cls");
        cout << "**********Menu de Listas Doble Enlazada**********" << endl;
        cout << "1. Lista de entero" << endl;
        cout << "2. Lista de flotantes" << endl;
        cout << "3. Lista de dobles" << endl;
        cout << "4. Lista de string" << endl;
        cout << "5. Lista de letras" << endl;
        cout << "6. Salir" << endl;
        opcion = ingresar_entero.ingresar("opcion","entero");
        cout << endl;
        switch(opcion) {
            case 1:
                do{ 
                system("cls");
                cout << "**********Menu de Listas de Enteros**********" << endl;
                cout << "1. Ingresar dato" << endl;
                cout << "2. Mostrar lista" << endl;
                cout << "3. Buscar dato" << endl;
                cout << "4. Eliminar dato" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("opcion","entero");
                cout << endl;
                switch(opcion){
                    case 1:
                        dato_entero = ingresar_entero.ingresar("dato","entero");
                        cout<<endl;
                        lista_entero->agregarAlInicio(dato_entero);
                        cout << "Dato agregado con exito" << endl;
                        system("pause");
                        break;
                    case 2:
                        lista_entero->mostrar();
                        system("pause");
                        break;
                    case 3:
                        dato_entero = ingresar_entero.ingresar("dato","entero");
                        cout<<endl;
                        lista_entero->buscar(dato_entero);
                        system("pause");
                        break;
                    case 4:
                        dato_entero = ingresar_entero.ingresar("dato","entero");
                        cout<<endl;
                        lista_entero->eliminar(dato_entero);
                        cout << "Dato eliminado con exito" << endl;
                        system("pause");
                        break;
                    case 5:
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                        system("pause");
                        break;
                        }
                    } while(opcion != 5);

                        break;
            case 2:
                do{
                system("cls");
                cout << "**********Menu de Listas de Flotantes**********" << endl;
                cout << "1. Ingresar dato" << endl;
                cout << "2. Mostrar lista" << endl;
                cout << "3. Buscar dato" << endl;
                cout << "4. Eliminar dato" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("opcion","entero");
                cout << endl;
                switch(opcion){
                    case 1:
                        dato_flotante = ingresar_flotante.ingresar("dato","flotante");
                        cout<<endl;
                        lista_flotantes->agregarAlInicio(dato_flotante);
                        cout << "Dato agregado con exito" << endl;
                        system("pause");
                        break;
                    case 2:
                        lista_flotantes->mostrar();
                        system("pause");
                        break;
                    case 3:
                        dato_flotante = ingresar_flotante.ingresar("dato","flotante");
                        cout<<endl;
                        lista_flotantes->buscar(dato_flotante);
                        system("pause");
                        break;
                    case 4:
                        dato_flotante = ingresar_flotante.ingresar("dato","flotante");
                        cout<<endl;
                        lista_flotantes->eliminar(dato_flotante);
                        cout << "Dato eliminado con exito" << endl;
                        system("pause");
                        break;
                    case 5:
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                        system("pause");
                        break;
                        }
                    } while(opcion != 5);
                        break;
            case 3:
                do{
                system("cls");
                cout << "**********Menu de Listas de Dobles**********" << endl;
                cout << "1. Ingresar dato" << endl;
                cout << "2. Mostrar lista" << endl;
                cout << "3. Buscar dato" << endl;
                cout << "4. Eliminar dato" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("opcion","entero");
                cout << endl;
                switch(opcion){
                    case 1:
                        dato_doble = ingresar_doble.ingresar("dato","doble");
                        cout<<endl;
                        lista_doble->agregarAlInicio(dato_doble);
                        cout << "Dato agregado con exito" << endl;
                        system("pause");
                        break;
                    case 2:
                        lista_doble->mostrar();
                        system("pause");
                        break;
                    case 3:
                        dato_doble = ingresar_doble.ingresar("dato","doble");
                        cout<<endl;
                        lista_doble->buscar(dato_doble);
                        system("pause");
                        break;
                    case 4:
                        dato_doble = ingresar_doble.ingresar("dato","doble");
                        cout<<endl;
                        lista_doble->eliminar(dato_doble);
                        cout << "Dato eliminado con exito" << endl;
                        system("pause");
                        break;
                    case 5:
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                        system("pause");
                        break;
                        }
                    } while(opcion != 5);
                        break;

            case 4:
                    do{
                    system("cls");
                    cout << "**********Menu de Listas de String**********" << endl;
                    cout << "1. Ingresar dato" << endl;
                    cout << "2. Mostrar lista" << endl;
                    cout << "3. Buscar dato" << endl;
                    cout << "4. Eliminar dato" << endl;
                    cout << "5. Salir" << endl;
                    opcion = ingresar_entero.ingresar("opcion","entero");
                    cout << endl;
                    switch(opcion){
                        case 1:
                            dato_string = ingresar_string.ingresar("dato","string");
                            cout<<endl;
                            lista_string->agregarAlInicio(dato_string);
                            cout << "Dato agregado con exito" << endl;
                            system("pause");
                            break;
                        case 2:
                            lista_string->mostrar();
                            system("pause");
                            break;
                        case 3:
                            dato_string = ingresar_string.ingresar("dato","string");
                            cout<<endl;
                            lista_string->buscar(dato_string);
                            system("pause");
                            break;
                        case 4:
                            dato_string = ingresar_string.ingresar("dato","string");
                            cout<<endl;
                            lista_string->eliminar(dato_string);
                            cout << "Dato eliminado con exito" << endl;
                            system("pause");
                            break;
                        case 5:
                            break;
                        default:
                            cout << "Opcion no valida" << endl;
                            system("pause");
                            break;
                            }
                        } while(opcion != 5);
                        break;
            case 5:
                    do{
                    system("cls");
                    cout << "**********Menu de Listas de Caracteres**********" << endl;
                    cout << "1. Ingresar dato" << endl;
                    cout << "2. Mostrar lista" << endl;
                    cout << "3. Buscar dato" << endl;
                    cout << "4. Eliminar dato" << endl;
                    cout << "5. Salir" << endl;
                    opcion = ingresar_entero.ingresar("opcion","entero");
                    cout << endl;
                    switch(opcion){
                        case 1:
                            dato_caracter = ingresar_caracter.ingresar("dato","caracter");
                            cout<<endl;
                            lista_caracter->agregarAlInicio(dato_caracter);
                            cout << "Dato agregado con exito" << endl;
                            system("pause");
                            break;
                        case 2:
                            lista_caracter->mostrar();
                            system("pause");
                            break;
                        case 3:
                            dato_caracter = ingresar_caracter.ingresar("dato","caracter");
                            cout<<endl;
                            lista_caracter->buscar(dato_caracter);
                            system("pause");
                            break;
                        case 4:
                            dato_caracter = ingresar_caracter.ingresar("dato","caracter");
                            cout<<endl;
                            lista_caracter->eliminar(dato_caracter);
                            cout << "Dato eliminado con exito" << endl;
                            system("pause");
                            break;
                        case 5:
                            break;
                        default:
                            cout << "Opcion no valida" << endl;
                            system("pause");
                            break;
                            }
                        } while(opcion != 5);
                        break;
            case 6: 
                cout << "Gracias por usar el programa" << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
                system("pause");
                break;
        }   
    } while(opcion != 6);
    return 0;
}