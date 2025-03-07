#include "Card.h"

Card::Card(sf::Font& font, const std::string& title) : font(font) {
    // Initialize background
    background.setFillColor(sf::Color(245, 245, 245));
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color(200, 200, 200));
    
    // Initialize title text
    titleText.setFont(font);
    titleText.setString(title);
    titleText.setCharacterSize(18);
    titleText.setFillColor(sf::Color(50, 50, 50));
    titleText.setStyle(sf::Text::Bold);
}

void Card::setPosition(float x, float y) {
    background.setPosition(x, y);
    
    // Position title text with some padding from the top
    titleText.setPosition(x + 10, y + 10);
}

void Card::setSize(float width, float height) {
    background.setSize(sf::Vector2f(width, height));
}

void Card::setBackgroundColor(sf::Color color) {
    background.setFillColor(color);
}

void Card::addElement(sf::Drawable* element) {
    childElements.push_back(element);
}

void Card::draw(sf::RenderWindow& window) {
    // Draw card background
    window.draw(background);
    
    // Draw title
    window.draw(titleText);
    
    // Draw all child elements
    for (auto element : childElements) {
        window.draw(*element);
    }
}

sf::Vector2f Card::getPosition() const {
    return background.getPosition();
}

sf::Vector2f Card::getSize() const {
    return background.getSize();
}