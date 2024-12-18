#include "Propietario.h"
#include "Validaciones.h"
#include "ListaPropietarios.h"
#include <algorithm>
#include "ValidacionPlaca.h"


using namespace std;

Propietario::Propietario()
    : nombre(""), apellido(""), cedula(""), correo("") {}


Propietario::Propietario(string nombre, string apellido, string cedula, string correo)
    : nombre(nombre), apellido(apellido), cedula(cedula), correo(correo) {}


void Propietario::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

void Propietario::setApellido(const string &apellido)
{
    this->apellido = apellido;
}

void Propietario::setCedula(const string &cedula)
{
    this->cedula = cedula;
}

void Propietario::setCorreo(const string &correo)
{
    this->correo = correo;
}

void Propietario::eliminarPlaca(const string &placa)
{
    auto it = find(placas.begin(), placas.end(), placa);
    if (it != placas.end())
    {
        placas.erase(it);
        cout << "Placa eliminada exitosamente." << endl;
    }
    else
    {
        cout << "Placa no encontrada." << endl;
    }
}

string Propietario::getNombre() const
{
    return nombre;
}

string Propietario::getApellido() const
{
    return apellido;
}

string Propietario::getCedula() const
{
    return cedula;
}

string Propietario::getCorreo() const
{
    return correo;
}



void Propietario::agregarPlaca(const string &placa)
{
    placas.push_back(placa);
}

vector<string> Propietario::getPlacas() const
{
    return placas;
}


string Propietario::toString() const
{
    string result = "Nombre: " + nombre + ", Apellido: " + apellido + ", Cedula: " + cedula + ", Correo: " + correo +  ", Placas: ";
    for (const auto &placa : placas)
    {
        result += placa + " ";
    }
    return result;
}


void agregarPropietario(ListaPropietarios &listaPropietarios)
{
    Validaciones validaciones;
    string nombre = validaciones.ingresarString("Ingrese el nombre del propietario: ");
    string apellido = validaciones.ingresarString("Ingrese el apellido del propietario: ");
    string cedula;
    do {
        cedula = validaciones.ingresarCedula("Ingrese la cedula del propietario: ");
        if (!validaciones.validarCedula(cedula)) {
            cout << "Cedula invalida. Intente de nuevo." << endl;
        }
    } while (!validaciones.validarCedula(cedula));
    
    string correo;
    do {
        correo = validaciones.ingresarCorreo("Ingrese el correo electronico del propietario: ");
        if (!validaciones.validarCorreo(correo)) {
            cout << "Correo invalido. Intente de nuevo." << endl;
        }
    } while (!validaciones.validarCorreo(correo));


    Propietario nuevoPropietario(nombre, apellido, cedula, correo);
    listaPropietarios.agregarPropietario(nuevoPropietario);

    cout << "Propietario agregado exitosamente." << endl;
}

void eliminarPlacaPropietario(ListaPropietarios &listaPropietarios)
{
    Placa<Coche> validador;
    Validaciones validaciones;
    string cedula = validaciones.ingresarCedula("Ingrese la cedula del propietario: ");
    Propietario* propietario = listaPropietarios.buscarPropietarioPorCedula(cedula);
    if (propietario != nullptr) {
        string placa = validador.ingresarPlaca(nullptr);
        propietario->eliminarPlaca(placa);
    } else {
        cout << "Propietario no encontrado." << endl;
    }
    system("pause");
}