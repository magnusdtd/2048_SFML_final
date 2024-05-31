#include "TextField.hpp"

TextField::TextField(unsigned int maxChars, float width, float height) :
    size(maxChars),
    rect(sf::Vector2f(width, height)),
    hasfocus(false)
{
    if (!font.loadFromFile("resources/arial.ttf"))
        std::cout << "Error loading font\n";
    rect.setOutlineThickness(2);
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color(127, 127, 127));
    rect.setPosition(this->getPosition());
}

const std::string TextField::getText() const {
    return text;
}

void TextField::setPosition(float x, float y) {
    sf::Transformable::setPosition(x, y);
    rect.setPosition(x, y);
}

bool TextField::contains(sf::Vector2f point) const {
    return rect.getGlobalBounds().contains(point);
}

void TextField::setFocus(bool focus) {
    hasfocus = focus;
    if (focus)
        rect.setOutlineColor(sf::Color::Blue);
    else
        rect.setOutlineColor(sf::Color(127, 127, 127));
}

void TextField::handleInput(sf::Event event) {
    if (!hasfocus || event.type != sf::Event::TextEntered)
        return;

    if (event.text.unicode == 8)   // Delete key
        text = text.substr(0, text.size() - 1);
    else if (text.size() < size)
        text += event.text.unicode;
}

void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rect, states); // Draw box

    /* Draw text */
    sf::Text t;
    t.setFont(font);
    t.setString(text);
    t.setOutlineThickness(0.1f);
	t.setPosition(rect.getPosition());
	t.setCharacterSize(25);
	t.setFillColor(sf::Color::Black);
	target.draw(t, states);
}
