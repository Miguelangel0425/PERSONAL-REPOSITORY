#pragma once 
#include <SFML/Graphics.hpp>
class Button {
    public:
        Button(sf::Font& font, const std::string& buttonText, float x, float y, float width, float height, sf::Color color);
        void centerText();
        void setPosition(float x, float y);
        void setString(const std::string& buttonText);
        void setFillColor(sf::Color color);
        bool isMouseOver(sf::Vector2i mousePos) const;
        void draw(sf::RenderWindow& window);
        sf::FloatRect getGlobalBounds() const;
    private:
        sf::RectangleShape shape;
        sf::Text text;
        sf::Font& font;
    };