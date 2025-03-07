#include "Screen.h"

Screen::Screen(sf::RenderWindow& window, sf::Font& font) 
    : window(window), font(font) {
    // Base constructor implementation
}

// Note: The draw(), handleEvent(), and update() methods are pure virtual,
// so they don't have implementations in the base class.