#include "ListaPropietarios.h"
#include <fstream>
#include <sstream>
#include "Lista.h"


void ListaPropietarios::agregarPropietario(const Propietario &propietario)
{
    propietarios.push_back(propietario);
}

Propietario* ListaPropietarios::buscarPropietarioPorCedula(const string &cedula)
{
    for (auto &propietario : propietarios)
    {
        if (propietario.getCedula() == cedula)
        {
            return &propietario;
        }
    }
    return nullptr;
}

void ListaPropietarios::mostrarPropietarios() const
{
    for (const auto &propietario : propietarios)
    {
        cout << propietario.toString() << endl;
    }
}

bool ListaPropietarios::estaVacia() const
{
    return propietarios.empty();
}
void ListaPropietarios::cargarArchivo(const string &archivo)
{
    ifstream file(archivo);
    if (file.is_open())
    {
        string linea;
        while (getline(file, linea))
        {
            stringstream ss(linea);
            string nombre, apellido, cedula, correo, placa;
            getline(ss, nombre, ',');
            getline(ss, apellido, ',');
            getline(ss, cedula, ',');
            getline(ss, correo, ',');
            Propietario propietario(nombre, apellido, cedula, correo );
            while (getline(ss, placa, ','))
            {
                propietario.agregarPlaca(ListaCircularDoble<Propietario>::descifrarTexto(placa));
            }
            agregarPropietario(propietario);
        }
        file.close();
    }
}

void ListaPropietarios::guardarArchivo(const string &archivo) const
{
    ofstream file(archivo);
    if (file.is_open())
    {
        for (const auto &propietario : propietarios)
        {
            file << propietario.getNombre() << ","
                 << propietario.getApellido() << ","
                 << propietario.getCedula() << ","
                 << propietario.getCorreo();
            for (const auto &placa : propietario.getPlacas())
            {
                file << "," << ListaCircularDoble<Propietario>::cifrarTexto(placa);
            }
            file << endl;
        }
        file.close();
    }
}