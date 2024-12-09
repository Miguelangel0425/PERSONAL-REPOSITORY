#include "../include/input_validator.h"
#include "input_validator.h"
#include <conio.h>
#include <iostream>

// Static member definitions
const std::regex InputValidator::plateRegex("^[A-Z]{3}\\d{3}$");
const std::regex InputValidator::letterRegex("^[A-Za-zÁÉÍÓÚáéíóúÑñ\\s]+$");
const std::regex InputValidator::numberRegex("^\\d+$");
const std::regex InputValidator::nameRegex("^[A-Za-zÁÉÍÓÚáéíóúÑñ\\s]+$");

bool InputValidator::isValidPlate(const std::string& plate) {
    std::regex plateRegex(
        "^([A-Z]{3}[0-9]{3,4})$|"   // Placas particulares (ABC123 o ABC1234)
        "^([A-Z]{2}[A-Z][0-9]{3,4})$|" // Placas transporte público (PBX123 o PBX1234)
        "^(CC[0-9]{3,4}[A-Z]?)$"    // Placas diplomáticas (CC1234A)
    );

    return std::regex_match(plate, plateRegex);
}

bool InputValidator::isOnlyLetters(const std::string& text) {
    return std::regex_match(text, letterRegex) && 
           !std::regex_search(text, numberRegex);
}

bool InputValidator::isOnlyNumbers(const std::string& text) {
    return std::regex_match(text, numberRegex);
}

bool InputValidator::isValidName(const std::string& name) {
    return isOnlyLetters(name);
}

bool InputValidator::isValidID(const std::string& id) {
    return isOnlyNumbers(id) && id.length() == 10;
}

bool InputValidator::isValidPhone(const std::string& phone) {
    return isOnlyNumbers(phone) && phone.length() == 10;
}

std::string InputValidator::getValidatedPlate() {
    std::string input;
    char ch;

    while (true) { 
        input.clear();
        std::cout << "Ingrese placa (solo letras y números, use DEL para borrar): ";

        while ((ch = _getch()) != '\r') { 
            if (std::isalnum(ch)) {
                ch = std::toupper(ch);
                std::cout << ch; 
                input += ch;
            } else if (ch == '\b' && !input.empty()) { 
                std::cout << "\b \b";
                input.pop_back();
            } else if (ch == '\b' && input.empty()) {
                continue;
            } else {
                continue;
            }
        }

        if (!input.empty()) {
            std::cout << "\n";
            return input;
        }

        std::cout << "\nEl campo no puede estar vacío. Intente nuevamente.\n";
    }
}
std::string InputValidator::getValidatedText() {
    std::string input;
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' es Enter
        if (isalpha(ch) || ch == ' ') {
            std::cout << ch; // Mostrar en pantalla
            input += ch;     // Agregar a la cadena
        } else if (ch == '\b' && !input.empty()) { // Backspace
            std::cout << "\b \b"; // Eliminar carácter en pantalla
            input.pop_back();     // Eliminar carácter en la cadena
        }
    }
    std::cout << std::endl; // Nueva línea al terminar
    return input;
}
std::string InputValidator::getValidatedNumber() {
    std::string input;
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' es Enter
        if (isdigit(ch)) {
            std::cout << ch; // Mostrar en pantalla
            input += ch;     // Agregar a la cadena
        } else if (ch == '\b' && !input.empty()) { // Backspace
            std::cout << "\b \b"; // Eliminar carácter en pantalla
            input.pop_back();     // Eliminar carácter en la cadena
        }
    }
    std::cout << std::endl; // Nueva línea al terminar
    return input;
}
std::string InputValidator::getValidatedDate() {
    std::string input;
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' es Enter
        if (isdigit(ch) || ch == '-') {
            std::cout << ch; 
            input += ch;    
        } else if (ch == '\b' && !input.empty()) { 
            std::cout << "\b \b"; 
            input.pop_back();     
        }
    }
    std::cout << std::endl; 
    return input;
}