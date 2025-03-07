#pragma once 
 #include <SFML/Graphics.hpp>

class InputField{

    private:
    sf::RectangleShape background;
    sf::Text text;
    sf::Font& font;
    std::string value;
    std::string placeholder;
    bool isFocused;

    public:
    InputField(sf::Font& font, const std::string& placeholder);
    void setPosition(float x, float y);
    void setSize(float width, float height);
    bool contains(sf::Vector2f point);
    void setFocus(bool focus);
    void handleTextInput(sf::Uint32 unicode);
    void draw(sf::RenderWindow& window);
    const std::string& getValue() const;
    void setValue(const std::string& newValue);
    void clear();
    bool isPassword;
};