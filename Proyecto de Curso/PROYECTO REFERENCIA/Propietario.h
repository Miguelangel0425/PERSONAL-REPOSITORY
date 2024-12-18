#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ListaPropietarios; // Forward declaration

class Propietario 
{
private:
    string nombre;
    string apellido;
    string cedula;
    string correo;
    vector<string> placas; 

public:

    Propietario();

    
    Propietario(string nombre, string apellido, string cedula, string correo);

    void setNombre(const string &nombre);
    void setApellido(const string &apellido);
    void setCedula(const string &cedula);
    void setCorreo(const string &correo);
    void eliminarPlaca(const string &placa);

   
    string getNombre() const;
    string getApellido() const;
    string getCedula() const;
    string getCorreo() const;

    
    void agregarPlaca(const string &placa);
    vector<string> getPlacas() const;

    
    string toString() const;
};


void agregarPropietario(ListaPropietarios &listaPropietarios);
void eliminarPlacaPropietario(ListaPropietarios &listaPropietarios);