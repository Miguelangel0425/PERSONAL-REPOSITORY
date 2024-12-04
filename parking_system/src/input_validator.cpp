#include "../include/input_validator.h"
#include <regex>

bool InputValidator::isValidPlate(const std::string& plate) {
    return std::regex_match(plate, std::regex("^[A-Z]{3}\\d{3}$"));
}

bool InputValidator::isValidName(const std::string& name) {
    return std::regex_match(name, std::regex("^[A-Za-zÁÉÍÓÚáéíóúÑñ\\s]+$")) 
           && !std::regex_search(name, std::regex("\\d"));
}

bool InputValidator::isValidID(const std::string& id) {
    return std::regex_match(id, std::regex("^\\d{10}$"));
}

bool InputValidator::isValidPhone(const std::string& phone) {
    return std::regex_match(phone, std::regex("^\\d{10}$"));
}