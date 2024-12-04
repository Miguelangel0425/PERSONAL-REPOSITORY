#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <string>

class InputValidator {
public:
    static bool isValidPlate(const std::string& plate);
    static bool isValidName(const std::string& name);
    static bool isValidID(const std::string& id);
    static bool isValidPhone(const std::string& phone);
};

#endif 