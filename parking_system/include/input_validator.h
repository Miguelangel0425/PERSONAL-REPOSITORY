#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <string>
#include <functional>
#include <regex>

class InputValidator {
public:
    template<typename T>
    static bool validate(const T& input, 
        std::function<bool(const T&)> customValidator = [](const T&) { return false; }) {
        if (customValidator) {
            return customValidator(input);
        }
        return false;
    }

    // Validadores específicos
    static bool isValidPlate(const std::string& plate);
    static bool isOnlyLetters(const std::string& text);
    static bool isOnlyNumbers(const std::string& text);
    static bool isValidName(const std::string& name);
    static bool isValidID(const std::string& id);
    static bool isValidPhone(const std::string& phone);

    static std::string getValidatedPlate();
    static std::string getValidatedText();
    static std::string getValidatedNumber();
    static std::string getValidatedDate();

private:
    // Regex para validaciones
    static const std::regex plateRegex;
    static const std::regex letterRegex;
    static const std::regex numberRegex;
    static const std::regex nameRegex;
};

#endif // INPUT_VALIDATOR_H