#pragma once 
#include <SFML/Graphics.hpp>

class FriendItem {
    private:
        sf::RectangleShape card;
        sf::Text nameText;
        sf::CircleShape avatar;
        sf::Font& font;
        bool isOnline;
        
    public:
        FriendItem(sf::Font& font, const std::string& name, bool online);
        void setPosition(float x, float y);
        void draw(sf::RenderWindow& window);
        float getHeight() const;
        bool contains(sf::Vector2f point);
    };