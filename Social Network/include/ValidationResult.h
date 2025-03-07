#pragma once 
#include <string>

class ValidationResult {
public:
    // Constructor
    ValidationResult(bool isValid = true, const std::string& errorMessage = "");
    
    // Getters
    bool isValid() const;
    std::string getErrorMessage() const;
    
    // Static factory methods for common validation results
    static ValidationResult success();
    static ValidationResult failure(const std::string& errorMessage);
    
private:
    bool m_isValid;
    std::string m_errorMessage;
};