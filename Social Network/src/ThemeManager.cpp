#include "ThemeManager.h"

ThemeManager::ThemeManager() {
    // Default theme (light)
    backgroundColor = sf::Color(240, 240, 240);
    primaryColor = sf::Color(0, 120, 215);
    secondaryColor = sf::Color(50, 160, 50);
    textColor = sf::Color(50, 50, 50);
    inputBackgroundColor = sf::Color(255, 255, 255);
    buttonHoverColor = sf::Color(0, 140, 240);
    errorColor = sf::Color(220, 50, 50);
}

ThemeManager& ThemeManager::getInstance() {
    static ThemeManager instance;
    return instance;
}

const sf::Color& ThemeManager::getBackgroundColor() const {
    return backgroundColor;
}

const sf::Color& ThemeManager::getPrimaryColor() const {
    return primaryColor;
}

const sf::Color& ThemeManager::getSecondaryColor() const {
    return secondaryColor;
}

const sf::Color& ThemeManager::getTextColor() const {
    return textColor;
}

const sf::Color& ThemeManager::getInputBackgroundColor() const {
    return inputBackgroundColor;
}

const sf::Color& ThemeManager::getButtonHoverColor() const {
    return buttonHoverColor;
}

const sf::Color& ThemeManager::getErrorColor() const {
    return errorColor;
}

void ThemeManager::setTheme(const std::string& themeName) {
    if (themeName == "dark") {
        // Dark theme
        backgroundColor = sf::Color(30, 30, 30);
        primaryColor = sf::Color(0, 102, 204);
        secondaryColor = sf::Color(46, 139, 87);
        textColor = sf::Color(240, 240, 240);
        inputBackgroundColor = sf::Color(50, 50, 50);
        buttonHoverColor = sf::Color(0, 122, 224);
        errorColor = sf::Color(230, 70, 70);
    } else if (themeName == "light") {
        // Light theme (default)
        backgroundColor = sf::Color(240, 240, 240);
        primaryColor = sf::Color(0, 120, 215);
        secondaryColor = sf::Color(50, 160, 50);
        textColor = sf::Color(50, 50, 50);
        inputBackgroundColor = sf::Color(255, 255, 255);
        buttonHoverColor = sf::Color(0, 140, 240);
        errorColor = sf::Color(220, 50, 50);
    }
}