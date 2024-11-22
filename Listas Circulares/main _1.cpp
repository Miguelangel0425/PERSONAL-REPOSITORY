/*************************
 * UFA-ESPE
 * ALUMNOS:  Leonardo Obando, William Leon
 * FECHA CREACION: Miercoles, 21 de noviembre de 2022
 * FECHA MODIFICACION: Miercoles, 23 de noviembre de 2022
 * Enunciado del problema: Crear los métodos Insertar, Buscar
 y Eliminar elementos de una lista Simple, Doble y Circular
 * Nivel: TERCERO     NRC: 7999
 *************************/
#include "ListasCirculares.cpp"
#include <stdlib.h>
using namespace std;

bool esEntero(string);

int main() {
    ListaCircular* lista = new ListaCircular();
    int opcion, dato;
    string linea, i, b, e, m, s;
    bool rep = true;
    bool repite = true;
    bool repetir = true;

    do {
        system("cls");
        cout << "***********Listas Circulares***********" << endl;
        cout << "1. Insertar" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Mostrar" << endl;
        cout << "5. Salir" << endl;
        do {
            cout << "Opcion: ";
            getline(cin, linea);

            if (esEntero(linea)) {
                repite = false;
                opcion = atoi(linea.c_str());
                if (opcion > 5 || opcion < 1) {
                    repetir = true;
                }
            }
            else {
                cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
            }
        } while (repite);
        opcion = atoi(linea.c_str());
        switch (opcion) {
        case 1:

            do {
                cout << "Ingrese el dato a insertar: ";
                getline(cin, i);

                if (esEntero(i)) {
                    rep = false;
                    dato = atoi(i.c_str());
                }
                else {
                    cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
                }
            } while (rep);
            dato = atoi(i.c_str());
            lista->Insertar(dato);
            break;
        case 2:
            do {
                cout << "Ingrese el dato a buscar: ";
                getline(cin, b);

                if (esEntero(b)) {
                    rep = false;
                    dato = atoi(b.c_str());
                }
                else {
                    cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
                }
            } while (rep);
            dato = atoi(b.c_str());
            lista->Buscar(dato);
            break;
        case 3:
            do {
                cout << "Ingrese el dato a eliminar: ";
                getline(cin, e);

                if (esEntero(e)) {
                    rep = false;
                    dato = atoi(e.c_str());
                }
                else {
                    cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
                }
            } while (rep);
            dato = atoi(e.c_str());
            lista->Eliminar(dato);
            break;
        case 4:
            lista->Mostrar();
            break;
        }
        system("pause");
    } while (opcion != 5);
    return 0;
}

//Fucion para validar
bool esEntero(string linea) {
    bool esEntero = true;
    int longitud = linea.size();

    if (longitud == 0) {
        esEntero = false;
    }
    else if (longitud == 1 && !isdigit(linea[0])) {
        esEntero = false;
    }
    else {
        int indice = 0;
        if (linea[0] == '+' || linea[0] == '-') {
            indice = 1;
        }
        else {
            indice = 0;
        }

        while (indice < longitud) {
            if (!isdigit(linea[indice])) {
                esEntero = false;
                break;
            }
            indice++;
        }
    }


    return esEntero;
}
