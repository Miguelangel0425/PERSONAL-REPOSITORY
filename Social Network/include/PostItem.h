#pragma once 
#include <SFML/Graphics.hpp>

class PostItem {
    private:
        sf::RectangleShape card;
        sf::Text contentText;
        sf::Text authorText;
        sf::Text timestampText;
        sf::Font& font;
        
    public:
        PostItem(sf::Font& font, const std::string& content, 
               const std::string& author, const std::string& timestamp);
        void setPosition(float x, float y);
        void draw(sf::RenderWindow& window);
        float getHeight() const;
    };