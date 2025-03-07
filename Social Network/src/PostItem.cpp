#include "PostItem.h"

PostItem::PostItem(sf::Font& font, const std::string& content, 
                 const std::string& author, const std::string& timestamp) 
    : font(font) {
    
    // Set up card background
    card.setFillColor(sf::Color(255, 255, 255));
    card.setOutlineThickness(1);
    card.setOutlineColor(sf::Color(200, 200, 200));
    
    // Configure author text
    authorText.setFont(font);
    authorText.setString(author);
    authorText.setCharacterSize(14);
    authorText.setStyle(sf::Text::Bold);
    authorText.setFillColor(sf::Color(50, 50, 50));
    
    // Configure content text
    contentText.setFont(font);
    contentText.setString(content);
    contentText.setCharacterSize(14);
    contentText.setFillColor(sf::Color(70, 70, 70));
    
    // Configure timestamp text
    timestampText.setFont(font);
    timestampText.setString(timestamp);
    timestampText.setCharacterSize(12);
    timestampText.setFillColor(sf::Color(150, 150, 150));
}

void PostItem::setPosition(float x, float y) {
    card.setPosition(x, y);
    
    // Position the text elements
    authorText.setPosition(x + 10, y + 10);
    contentText.setPosition(x + 10, y + 35);
    timestampText.setPosition(x + 10, y + card.getSize().y - 25);
}

void PostItem::draw(sf::RenderWindow& window) {
    window.draw(card);
    window.draw(authorText);
    window.draw(contentText);
    window.draw(timestampText);
}

float PostItem::getHeight() const {
    return card.getSize().y;
}