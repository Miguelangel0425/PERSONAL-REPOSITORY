#pragma once
#include <SFML/Graphics.hpp>

enum class MessageType { Error, Success, Info };

class PopupMessage {
    private:
        sf::RectangleShape background;
        sf::Text messageText;
        sf::Font& font;
        sf::Clock lifetime;
        float duration;
        MessageType type;
        
    public:
        PopupMessage(sf::Font& font, const std::string& message, 
                    MessageType type, float duration = 3.0f);
        void draw(sf::RenderWindow& window);
        bool isExpired() const;
        void setPosition(float x, float y);
    };