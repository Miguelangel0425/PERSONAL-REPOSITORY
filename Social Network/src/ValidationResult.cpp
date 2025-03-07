#include "ValidationResult.h"

// Constructor
ValidationResult::ValidationResult(bool isValid, const std::string& errorMessage)
    : m_isValid(isValid), m_errorMessage(errorMessage) {
}

// Getters
bool ValidationResult::isValid() const {
    return m_isValid;
}

std::string ValidationResult::getErrorMessage() const {
    return m_errorMessage;
}

// Static factory methods
ValidationResult ValidationResult::success() {
    return ValidationResult(true, "");
}

ValidationResult ValidationResult::failure(const std::string& errorMessage) {
    return ValidationResult(false, errorMessage);
}