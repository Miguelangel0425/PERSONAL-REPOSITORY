#include "FriendItem.h"

FriendItem::FriendItem(sf::Font& font, const std::string& name, bool online) 
    : font(font), isOnline(online) {
    
    // Set up card background
    card.setFillColor(sf::Color(255, 255, 255));
    card.setOutlineThickness(1);
    card.setOutlineColor(sf::Color(200, 200, 200));
    card.setSize(sf::Vector2f(200, 50));
    
    // Configure name text
    nameText.setFont(font);
    nameText.setString(name);
    nameText.setCharacterSize(14);
    nameText.setFillColor(sf::Color(50, 50, 50));
    
    // Set up avatar circle
    avatar.setRadius(15);
    avatar.setFillColor(sf::Color(220, 220, 220));
    avatar.setOutlineThickness(1);
    avatar.setOutlineColor(sf::Color(180, 180, 180));
}

void FriendItem::setPosition(float x, float y) {
    card.setPosition(x, y);
    
    // Position avatar on the left side
    avatar.setPosition(x + 10, y + 10);
    
    // Position name text next to avatar
    nameText.setPosition(x + 50, y + (card.getSize().y - nameText.getCharacterSize()) / 2);
    
    // Add online indicator
    if (isOnline) {
        sf::CircleShape statusIndicator;
        statusIndicator.setRadius(5);
        statusIndicator.setFillColor(sf::Color::Green);
        statusIndicator.setPosition(x + card.getSize().x - 20, y + card.getSize().y - 15);
    }
}

void FriendItem::draw(sf::RenderWindow& window) {
    window.draw(card);
    window.draw(avatar);
    window.draw(nameText);
    
    // Draw online status indicator
    if (isOnline) {
        sf::CircleShape statusIndicator;
        statusIndicator.setRadius(5);
        statusIndicator.setFillColor(sf::Color::Green);
        statusIndicator.setPosition(
            card.getPosition().x + card.getSize().x - 15, 
            card.getPosition().y + card.getSize().y - 15
        );
        window.draw(statusIndicator);
    }
}

float FriendItem::getHeight() const {
    return card.getSize().y;
}

bool FriendItem::contains(sf::Vector2f point) {
    return card.getGlobalBounds().contains(point);
}