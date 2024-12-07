#include "../include/input_validator.h"

// Static member definitions
const std::regex InputValidator::plateRegex("^[A-Z]{3}\\d{3}$");
const std::regex InputValidator::letterRegex("^[A-Za-zÁÉÍÓÚáéíóúÑñ\\s]+$");
const std::regex InputValidator::numberRegex("^\\d+$");
const std::regex InputValidator::nameRegex("^[A-Za-zÁÉÍÓÚáéíóúÑñ\\s]+$");

bool InputValidator::isValidPlate(const std::string& plate) {
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