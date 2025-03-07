#pragma once 
#include <SFML/Graphics.hpp>

class Card {
    private:
        sf::RectangleShape background;
        sf::Text titleText;
        sf::Font& font;
        std::vector<sf::Drawable*> childElements;
        
    public:
        Card(sf::Font& font, const std::string& title);
        void setPosition(float x, float y);
        void setSize(float width, float height);
        void setBackgroundColor(sf::Color color);
        void addElement(sf::Drawable* element);
        void draw(sf::RenderWindow& window);
        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
    };