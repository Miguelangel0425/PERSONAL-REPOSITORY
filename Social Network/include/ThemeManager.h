#pragma once 
#include <SFML/Graphics.hpp>

class ThemeManager {
    private:
        sf::Color backgroundColor;
        sf::Color primaryColor;
        sf::Color secondaryColor;
        sf::Color textColor;
        sf::Color inputBackgroundColor;
        sf::Color buttonHoverColor;
        sf::Color errorColor;
        
    public:
        ThemeManager();
        static ThemeManager& getInstance();
        const sf::Color& getBackgroundColor() const;
        const sf::Color& getPrimaryColor() const;
        const sf::Color& getSecondaryColor() const;
        const sf::Color& getTextColor() const;
        const sf::Color& getInputBackgroundColor() const;
        const sf::Color& getButtonHoverColor() const;
        const sf::Color& getErrorColor() const;
        
        void setTheme(const std::string& themeName); // Para cambiar entre temas claros/oscuros
    };