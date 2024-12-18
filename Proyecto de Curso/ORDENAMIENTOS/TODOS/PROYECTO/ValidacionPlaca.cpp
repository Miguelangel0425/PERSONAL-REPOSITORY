#include "ValidacionPlaca.h"
#include <unordered_set>
#include <regex>
#include <algorithm>
#include <stdexcept>

template <typename T>
string Placa<T>::ingresarPlaca(Nodo<T> *aux)
{
    string placa;
    unordered_set<string> provinciasValidas = {
        "A", "B", "C", "E", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    while (true)
    {
        placa = "";
        cout << "Ingrese la placa: ";
        getline(cin, placa);

        placa.erase(remove(placa.begin(), placa.end(), ' '), placa.end());

        if (placa.length() != 7)
        {
            cout << "\nLa placa debe tener exactamente 7 caracteres. Intente de nuevo." << endl;
            continue;
        }

        if (provinciasValidas.count(string(1, toupper(placa[0]))) == 0)
        {
            cout << "\nInicial de provincia no válida. Intente de nuevo." << endl;
            continue;
        }

        if (!regex_match(placa, regex("^[A-Z]{1,3}[0-9]{4}$")))
        {
            cout << "\nFormato de placa incorrecto. Intente de nuevo." << endl;
            continue;
        }

        break;
    }

    return placa;
}


template class Placa<Coche>;