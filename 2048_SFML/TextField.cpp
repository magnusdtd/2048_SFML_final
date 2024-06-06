#include "TextField.hpp"

/**
 * Constructor that initializes the text field with a maximum number of characters and dimensions.
 */
TextField::TextField(unsigned int maxChars, float width, float height) :
    size(maxChars),
    rect(sf::Vector2f(width, height)),
    hasfocus(false)
{
    pressTime = 0.0f;
    if (!font.loadFromFile("Fonts/arial.ttf"))
        std::cout << "Error loading font\n";
    rect.setOutlineThickness(2);
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color(127, 127, 127));
    rect.setPosition(this->getPosition());
}

/**
 * Returns the text entered in the text field.
 */
const std::string TextField::getText() const {
    return text;
}

/**
 * Sets the position of the text field.
 */
void TextField::setPosition(float x, float y) {
    sf::Transformable::setPosition(x, y);
    rect.setPosition(x, y);
}

/**
 * Checks if a point is within the text field.
 */
bool TextField::contains(sf::Vector2f point) const {
    return rect.getGlobalBounds().contains(point);
}

/**
 * Sets the focus of the text field.
 */
void TextField::setFocus(bool focus) {
    hasfocus = focus;
    if (focus)
        rect.setOutlineColor(sf::Color::Blue);
    else
        rect.setOutlineColor(sf::Color(127, 127, 127));
}

/**
 * Handles input events for the text field.
 */
void TextField::handleInput(sf::Event event, float deltaTime) {
    if (!hasfocus || event.type != sf::Event::TextEntered)
        return;
    std::cout << event.text.unicode << std::endl;

    if (!((event.text.unicode >= 48 && event.text.unicode <= 57) || // Number
        (event.text.unicode >= 65 && event.text.unicode <= 90) ||   // Uppercase
        (event.text.unicode >= 97 && event.text.unicode <= 122) ||  // Lowercase
        event.text.unicode == 8)) {
        isWarnning = true;
        return;
    }

    pressTime -= PRESS_DELAY;
    if (event.text.unicode == 8 && pressTime <= 0.f) {  // Delete key
        text = text.substr(0, text.size() - 1);
        pressTime = PRESS_DELAY;
    }
    else if (text.size() < size && pressTime <= 0.f) {
        text += event.text.unicode;
        pressTime = PRESS_DELAY;
    }
}

/**
 * Clears the text field.
 */
void TextField::clear() {
    text = "";
}

/**
 * Draws the text field on a render target.
 */
void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect, states); // Draw box

    /* Draw text */
    sf::Text t;
    t.setFont(font);
    t.setString(text);
    t.setOutlineThickness(0.1f);
    t.setPosition(rect.getPosition() + sf::Vector2f(7.f, 0.f));
    t.setCharacterSize(25);
    t.setFillColor(sf::Color::Black);
    target.draw(t, states);

    /* Draw instruction text */
    t.setString("Enter your name");
    t.setPosition(rect.getPosition() + sf::Vector2f(7.f, -45.f));
    t.setCharacterSize(40);
    t.setFillColor(sf::Color::Black);
    target.draw(t, states);

    /* Draw warnning */
    if (isWarnning) {
        t.setString("Name must only contain number 0-9, letter A-Z, a-z ans NO space!!!");
        t.setPosition(rect.getPosition() + sf::Vector2f(7.f, 35.f));
        t.setCharacterSize(30);
        t.setFillColor(sf::Color::Red);
        target.draw(t, states);
    }
}
