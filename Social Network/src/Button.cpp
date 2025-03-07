#include <Button.h>

Button::Button(sf::Font& font, const std::string& buttonText, float x, float y, float width, float height, sf::Color color)
: font(font) {
// Configurar forma
shape.setSize(sf::Vector2f(width, height));
shape.setPosition(x, y);
shape.setFillColor(color);
shape.setOutlineThickness(2);
shape.setOutlineColor(sf::Color(100, 100, 100));

// Configurar texto
text.setFont(font);
text.setString(buttonText);
text.setCharacterSize(16);
text.setFillColor(sf::Color::White);

// Centrar texto
void centerText();
}

void Button:: centerText() {
sf::FloatRect textBounds = text.getLocalBounds();
sf::FloatRect shapeBounds = shape.getGlobalBounds();
text.setPosition(
    shapeBounds.left + (shapeBounds.width - textBounds.width) / 2,
    shapeBounds.top + (shapeBounds.height - textBounds.height) / 2
);
}

void Button::setPosition(float x, float y) {
shape.setPosition(x, y);
centerText();
}

void Button::setString(const std::string& buttonText) {
text.setString(buttonText);
centerText();
}

void Button::setFillColor(sf::Color color) {
shape.setFillColor(color);
}

bool Button::isMouseOver(sf::Vector2i mousePos) const {
return shape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Button::draw(sf::RenderWindow& window) {
window.draw(shape);
window.draw(text);
}

sf::FloatRect Button::getGlobalBounds() const {
return shape.getGlobalBounds();
}