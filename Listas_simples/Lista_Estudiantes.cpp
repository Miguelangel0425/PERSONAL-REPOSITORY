#include "Lista_Simple.cpp"
#include "Nodo.cpp"
#include "Validaciones.cpp"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Validación de nombres y apellidos
bool validarNombre(const string& nombre) {
    if (nombre.empty()) return false;
    for (char c : nombre) {
        if (!isalpha(c) && c != ' ' && c != 'á' && c != 'é' && c != 'í' && c != 'ó' && c != 'ú' &&
            c != 'Á' && c != 'É' && c != 'Í' && c != 'Ó' && c != 'Ú' && c != 'ñ' && c != 'Ñ') {
            return false;
        }
    }
    return true;
}

// Validación de cédula
bool validarCedula(const string& cedula) {
    if (cedula.empty()) return false;
    for (char c : cedula) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Generación de correos
string generarCorreo(const string& nombre, const string& apellido) {
    string correo;
    correo += nombre[0]; // Primera letra del nombre
    correo += apellido; // Primer apellido completo
    correo += "@espe.edu.ec";
    return correo;
}

int main() {
    Lista_Simple<string>* lista_estudiantes = new Lista_Simple<string>();
    Validaciones<string> validador;

    int opcion;
    string nombre, apellido, cedula;

    do {
        system("cls");
        cout << "*********** Gestion de Estudiantes ***********" << endl;
        cout << "1. Insertar estudiante" << endl;
        cout << "2. Mostrar lista de estudiantes" << endl;
        cout << "3. Salir" << endl;
        opcion = stoi(validador.ingresar("Seleccione una opcion: ", "entero"));

        switch (opcion) {
        case 1: {
            string nombre, apellido, cedula;
            do {
                cout << "Ingrese el nombre: ";
                getline(cin >> ws, nombre);
                if (!validarNombre(nombre)) {
                    cout << "Nombre invalido. Intente nuevamente. Solo letras y espacios permitidos." << endl;
                }
            } while (!validarNombre(nombre));

            do {
                cout << "Ingrese el apellido: ";
                getline(cin >> ws, apellido);
                if (!validarNombre(apellido)) {
                    cout << "Apellido invalido. Intente nuevamente. Solo letras y espacios permitidos." << endl;
                }
            } while (!validarNombre(apellido));

            do {
                cout << "Ingrese la cedula: ";
                getline(cin >> ws, cedula);
                if (!validarCedula(cedula)) {
                    cout << "Cedula invalida. Intente nuevamente. Solo numeros permitidos." << endl;
                }
            } while (!validarCedula(cedula));

            // Generar correo y concatenar la información
            string correo = generarCorreo(nombre, apellido);
            string estudiante = "Nombre: " + nombre + " " + apellido + ", Cedula: " + cedula + ", Correo: " + correo;
            lista_estudiantes->Insertar_cabeza(estudiante);

            cout << "Estudiante agregado exitosamente!" << endl;
            system("pause");
            break;
        }
        case 2:
            cout << "Lista de Estudiantes:" << endl;
            lista_estudiantes->Mostrar();
            system("pause");
            break;

        case 3:
            cout << "Gracias por utilizar el sistema." << endl;
            break;

        default:
            cout << "Opcion no valida, intente nuevamente." << endl;
            system("pause");
            break;
        }
    } while (opcion != 3);

    delete lista_estudiantes;
    return 0;
}
