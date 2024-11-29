/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista doble enlazada                  *
 * Autor:                          Josue Chango, Adonny Calero, Eduardo altamirano     *
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


            }while(opcion != 5);
                        
    }
        
    }
}while(opcion != 6);
}