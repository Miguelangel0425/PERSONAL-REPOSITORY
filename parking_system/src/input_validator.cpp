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
    // Códigos de provincias válidos
    const std::vector<std::string> provinceCodes = {
        "A", "W", "Q", "B", "G", "S", "U", "I", "P", 
        "C", "L", "Y", "H", "R", "J", "X", "M", "K", 
        "O", "V", "T", "E", "N", "Z"
    };

    // Códigos especiales
    const std::vector<std::string> specialCodes = {
        "CC", "CD", "OI", "AT", "IT"
    };

    // Convertir a mayúsculas para validación consistente
    std::string upperPlate = plate;
    std::transform(upperPlate.begin(), upperPlate.end(), upperPlate.begin(), ::toupper);

    // Validar placas de provincias
    if (upperPlate.length() == 6 || upperPlate.length() == 7) {
        // Verificar si el primer código es un código de provincia válido
        auto it = std::find(provinceCodes.begin(), provinceCodes.end(), upperPlate.substr(0, 1));
        if (it != provinceCodes.end()) {
            // Verificar que los siguientes 2 caracteres sean letras
            for (int i = 1; i < 3; ++i) {
                if (!std::isalpha(upperPlate[i])) {
                    return false;
                }
            }
            
            // Verificar que los últimos 3-4 caracteres sean números
            for (size_t i = 3; i < upperPlate.length(); ++i) {
                if (!std::isdigit(upperPlate[i])) {
                    return false;
                }
            }
            return true;
        }
    }

    // Validar placas especiales
    if (upperPlate.length() >= 4) {
        auto it = std::find(specialCodes.begin(), specialCodes.end(), upperPlate.substr(0, 2));
        if (it != specialCodes.end()) {
            // Verificar que hay números después del código especial
            for (size_t i = 2; i < upperPlate.length(); ++i) {
                if (!std::isdigit(upperPlate[i])) {
                    return false;
                }
            }
            return true;
        }
    }

    // Verificar placas de internación temporal con color
    if (upperPlate.length() >= 8) {
        if ((upperPlate.substr(0, 2) == "IT") && 
            (upperPlate.substr(2, 4) == "-AZUL" || upperPlate.substr(2, 4) == "-ROJO")) {
            for (size_t i = 6; i < upperPlate.length(); ++i) {
                if (!std::isdigit(upperPlate[i])) {
                    return false;
                }
            }
            return true;
        }
    }

    return false;
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
    // Verificar que la cédula tenga exactamente 10 dígitos
    if (id.length() != 10 || !std::all_of(id.begin(), id.end(), ::isdigit)) {
        return false;
    }

    // Validar que el primer dígito corresponde a una provincia válida (1-9)
    int provinceCode = id[0] - '0';
    if (provinceCode < 1 || provinceCode > 9) {
        return false;
    }

    // Algoritmo para verificar el dígito verificador
    int sum = 0;
    int multipliers[9] = {2, 1, 2, 1, 2, 1, 2, 1, 2};

    for (int i = 0; i < 9; ++i) {
        int digit = id[i] - '0';  // Convertir el carácter a número
        sum += digit * multipliers[i];
    }

    // Calcular el dígito verificador
    int remainder = sum % 10;
    int checkDigit = (remainder == 0) ? 0 : 10 - remainder;

    // Validar que el dígito verificador coincida con el décimo dígito de la cédula
    return checkDigit == (id[9] - '0');
}

bool InputValidator::isValidPhone(const std::string& phone) {
    // Verificar que el número de teléfono tenga exactamente 10 dígitos
    if (phone.length() != 10 || !std::all_of(phone.begin(), phone.end(), ::isdigit)) {
        return false;
    }

    // Verificar que empiece con "09" (prefijo válido de celular ecuatoriano)
    if (phone.substr(0, 2) != "09") {
        return false;
    }

    return true;
}

std::string InputValidator::getValidatedPlate() {
    std::string input;
    char ch;

    while (true) { 
        input.clear();

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