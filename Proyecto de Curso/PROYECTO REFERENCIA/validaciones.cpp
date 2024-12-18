#include "Validaciones.h"  
#include <iostream>
#include <conio.h>
#include <regex>

string Validaciones::ingresarString(const string &msj)
{
    string input;
    char c;

    cout << msj;

    while (true)
    {
        c = getch();  

        if (isalpha(c))
        {
            input += c;
            cout << c;
        }
        else if (c == '\b' && !input.empty())  
        {
            input.pop_back();
            cout << "\b \b";
        }
        else if (c == '\r')  
        {
            if (!input.empty())  
            {
                break;
            }
            else
            {
                cout << "\a";  
            }
        }
        else
        {
            cout << "\a";  
        }
    }

    cout << endl;
    return input;
}

string Validaciones::ingresarCedula(const string &msj)
{
    string cedula;
    char c;

    cout << msj;

    while (true)
    {
        c = _getch();  

        if (isdigit(c))
        {
            cedula += c;
            cout << c;
        }
        else if (c == '\b' && !cedula.empty())  
        {
            cedula.pop_back();
            cout << "\b \b";
        }
        else if (c == '\r')  
        {
            if (!cedula.empty())  
            {
                break;
            }
            else
            {
                cout << "\a";  
            }
        }
        else
        {
            cout << "\a";  
        }
    }

    cout << endl;
    return cedula;
}

string Validaciones::ingresarCorreo(const string &msj)
{
    string correo;
    cout << msj;
    cin >> correo;
    return correo;
}

bool Validaciones::validarCedula(const string &cedula)
{
    if (cedula.length() != 10)
    {
        return false;
    }

    int suma = 0;
    for (int i = 0; i < 9; i++)
    {
        int digito = cedula[i] - '0';
        if (i % 2 == 0)
        {
            digito *= 2;
            if (digito > 9)
            {
                digito -= 9;
            }
        }
        suma += digito;
    }

    int ultimoDigito = cedula[9] - '0';
    int digitoVerificador = (10 - (suma % 10)) % 10;

    return ultimoDigito == digitoVerificador;
}

bool Validaciones::validarCorreo(const string &correo)
{
    const regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.{1}\w+)+)");
    return regex_match(correo, pattern);
}