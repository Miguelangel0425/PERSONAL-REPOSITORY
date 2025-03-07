#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "InputField.h"
#include "Card.h"  

class Screen {
    protected:
        sf::RenderWindow& window;
        sf::Font& font;
        std::vector<Button*> buttons;
        std::vector<InputField*> inputs;
        std::vector<Card*> cards;
        
    public:
        Screen(sf::RenderWindow& window, sf::Font& font);
        virtual void draw() = 0;
        virtual void handleEvent(sf::Event& event) = 0;
        virtual void update() = 0;
        virtual ~Screen() = default;
    };

