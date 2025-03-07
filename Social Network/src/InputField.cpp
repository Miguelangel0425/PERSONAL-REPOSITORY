#include "InputField.h"

InputField::InputField(sf::Font& font, const std::string& placeholder)
    : font(font), placeholder(placeholder), isFocused(false), isPassword(false) {
    background.setFillColor(sf::Color(240, 240, 240));
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color(200, 200, 200));
    
    text.setFont(font);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::Black);
}

void InputField::setPosition(float x, float y) {
    background.setPosition(x, y);
    // Position the text with a small padding
    text.setPosition(x + 5, y + background.getSize().y / 2 - text.getCharacterSize() / 2);
}

void InputField::setSize(float width, float height) {
    background.setSize(sf::Vector2f(width, height));
    // Adjust text position based on new size
    text.setPosition(
        background.getPosition().x + 5,
        background.getPosition().y + background.getSize().y / 2 - text.getCharacterSize() / 2
    );
}

bool InputField::contains(sf::Vector2f point) {
    return background.getGlobalBounds().contains(point);
}

void InputField::setFocus(bool focus) {
    isFocused = focus;
    if (isFocused) {
        background.setOutlineColor(sf::Color(0, 120, 215));
        background.setOutlineThickness(2);
    } else {
        background.setOutlineColor(sf::Color(200, 200, 200));
        background.setOutlineThickness(1);
    }
}

void InputField::handleTextInput(sf::Uint32 unicode) {
    if (!isFocused) return;
    
    if (unicode == 8) { // Backspace
        if (!value.empty()) {
            value.pop_back();
        }
    } 
    else if (unicode == 13) { // Enter
        // Enter key handling can be implemented if needed
    } 
    else if (unicode >= 32 && unicode < 128) { // Standard ASCII characters
        value += static_cast<char>(unicode);
    }
}

void InputField::draw(sf::RenderWindow& window) {
    window.draw(background);
    
    if (value.empty() && !isFocused) {
        // Show placeholder text
        text.setString(placeholder);
        text.setFillColor(sf::Color(150, 150, 150));
    } else {
        // Show actual input text or password mask
        if (isPassword) {
            text.setString(std::string(value.length(), '*'));
        } else {
            text.setString(value);
        }
        text.setFillColor(sf::Color::Black);
    }
    
    window.draw(text);
}

const std::string& InputField::getValue() const {
    return value;
}

void InputField::setValue(const std::string& newValue) {
    value = newValue;
}

void InputField::clear() {
    value.clear();
}

