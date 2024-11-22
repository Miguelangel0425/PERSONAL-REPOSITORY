#include "Lista_Simple.h"
#include "Nodo.h"
#include "Validaciones.h"
#include <iostream>
#include <string>
#include <cctype>
#include <random>
#include <sstream>
#include <algorithm>

using namespace std;

class Sistema_Estudiantes {
private:
    Lista_Simple<string>* lista_estudiantes;
    
    bool correoExiste(const string& correo) {
        Nodo<string>* aux = lista_estudiantes->getCabeza();
        while (aux != nullptr) {
            string datos = aux->getDato();
            size_t pos = datos.find("Correo: ");
            if (pos != string::npos) {
                string correoActual = datos.substr(pos + 8);
                correoActual = correoActual.substr(0, correoActual.find(","));
                if (correoActual == correo) {
                    return true;
                }
            }
            aux = aux->getSiguiente();
        }
        return false;
    }
    
    string generarNumeroRandom() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(100, 999);
        return to_string(dis(gen));
    }
    
    string generarCorreo(const string& nombre, const string& apellido) {
        string nombreMin = nombre;
        string apellidoMin = apellido;
        
        // Convertir a minúsculas y remover caracteres especiales
        string resultado;
        for (char c : nombreMin) {
            if (c == '\xE1') resultado += 'a';      // á
            else if (c == '\xE9') resultado += 'e'; // é
            else if (c == '\xED') resultado += 'i'; // í
            else if (c == '\xF3') resultado += 'o'; // ó
            else if (c == '\xFA') resultado += 'u'; // ú
            else if (c == '\xF1') resultado += 'n'; // ñ
            else resultado += tolower(c);
        }
        nombreMin = resultado;
        
        resultado.clear();
        for (char c : apellidoMin) {
            if (c == '\xE1') resultado += 'a';      // á
            else if (c == '\xE9') resultado += 'e'; // é
            else if (c == '\xED') resultado += 'i'; // í
            else if (c == '\xF3') resultado += 'o'; // ó
            else if (c == '\xFA') resultado += 'u'; // ú
            else if (c == '\xF1') resultado += 'n'; // ñ
            else resultado += tolower(c);
        }
        apellidoMin = resultado;
        
        // Remover espacios
        nombreMin.erase(remove(nombreMin.begin(), nombreMin.end(), ' '), nombreMin.end());
        apellidoMin.erase(remove(apellidoMin.begin(), apellidoMin.end(), ' '), apellidoMin.end());
        
        // Generar correo base
        string correoBase = nombreMin[0] + apellidoMin + "@espe.edu.ec";
        string correo = correoBase;
        
        // Si el correo ya existe, añadir número aleatorio
        while (correoExiste(correo)) {
            correo = correoBase.substr(0, correoBase.find("@")) + 
                    generarNumeroRandom() + "@espe.edu.ec";
        }
        
        return correo;
    }

    bool validarNombre(const string& nombre) {
        if (nombre.empty() || nombre.length() < 2) return false;
        
        for (unsigned char c : nombre) {
            if (!isalpha(c) && c != ' ' && 
                c != '\xE1' && c != '\xE9' && c != '\xED' && c != '\xF3' && c != '\xFA' && // á é í ó ú
                c != '\xC1' && c != '\xC9' && c != '\xCD' && c != '\xD3' && c != '\xDA' && // Á É Í Ó Ú
                c != '\xF1' && c != '\xD1') { // ñ Ñ
                return false;
            }
        }
        return true;
    }

    bool validarCedula(const string& cedula) {
        if (cedula.length() != 10) return false;
        
        for (char c : cedula) {
            if (!isdigit(c)) {
                return false;
            }
        }
        
        // Algoritmo de validación de cédula ecuatoriana
        int suma = 0;
        for (int i = 0; i < 9; i++) {
            int digito = cedula[i] - '0';
            if (i % 2 == 0) {
                digito *= 2;
                if (digito > 9) digito -= 9;
            }
            suma += digito;
        }
        int verificador = (10 - (suma % 10)) % 10;
        return verificador == (cedula[9] - '0');
    }

    int ingresarEntero(const string& mensaje) {
        int valor;
        while (true) {
            cout << mensaje;
            string entrada;
            getline(cin, entrada);
            try {
                valor = stoi(entrada);
                if (valor < 1 || valor > 3) {
                    cout << "Por favor, ingrese una opción válida (1-3)." << endl;
                    continue;
                }
                break;
            } catch (const invalid_argument& e) {
                cout << "Por favor, ingrese un número válido." << endl;
            }
        }
        return valor;
    }

public:
    Sistema_Estudiantes() {
        lista_estudiantes = new Lista_Simple<string>();
    }
    
    ~Sistema_Estudiantes() {
        delete lista_estudiantes;
    }

    void ejecutar() {
        int opcion;
        string nombre, apellido, cedula;

        do {
            system("cls");
            cout << "\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557" << endl;
            cout << "\u2551      Gestión de Estudiantes ESPE       \u2551" << endl;
            cout << "\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563" << endl;
            cout << "\u2551 1. Insertar estudiante                 \u2551" << endl;
            cout << "\u2551 2. Mostrar lista de estudiantes        \u2551" << endl;
            cout << "\u2551 3. Salir                              \u2551" << endl;
            cout << "\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D" << endl;
            
            opcion = ingresarEntero("Seleccione una opción: ");

            switch (opcion) {
            case 1: {
                cout << "\n--- Registro de Nuevo Estudiante ---\n" << endl;
                do {
                    cout << "Ingrese el nombre: ";
                    getline(cin >> ws, nombre);
                    if (!validarNombre(nombre)) {
                        cout << "Nombre inválido. Use solo letras y espacios." << endl;
                    }
                } while (!validarNombre(nombre));

                do {
                    cout << "Ingrese el apellido: ";
                    getline(cin >> ws, apellido);
                    if (!validarNombre(apellido)) {
                        cout << "Apellido inválido. Use solo letras y espacios." << endl;
                    }
                } while (!validarNombre(apellido));

                do {
                    cout << "Ingrese la cédula: ";
                    getline(cin >> ws, cedula);
                    if (!validarCedula(cedula)) {
                        cout << "Cédula inválida. Debe ser una cédula ecuatoriana válida de 10 dígitos." << endl;
                    }
                } while (!validarCedula(cedula));

                string correo = generarCorreo(nombre, apellido);
                string estudiante = "Nombre: " + nombre + " " + apellido + 
                                  ", Cédula: " + cedula + 
                                  ", Correo: " + correo;
                
                lista_estudiantes->Insertar_cola(estudiante);

                cout << "\n¡Estudiante agregado exitosamente!" << endl;
                cout << "Correo generado: " << correo << endl;
                system("pause");
                break;
            }
            case 2:
                cout << "\nLista de Estudiantes:" << endl;
                cout << "----------------------------------------" << endl;
                lista_estudiantes->Mostrar();
                cout << "----------------------------------------" << endl;
                system("pause");
                break;

            case 3:
                cout << "\nGracias por utilizar el sistema." << endl;
                break;
            }
        } while (opcion != 3);
    }
};

int main() {
    Sistema_Estudiantes sistema;
    sistema.ejecutar();
    return 0;
}