#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "utils.hpp"

/**
 * TextField class represents a text input field in a graphical user interface.
 * It inherits from sf::Drawable and sf::Transformable to be drawable and transformable in a SFML window.
 */
class TextField : public sf::Drawable, public sf::Transformable {
private:
    std::string text;  // The text entered in the text field
    sf::RectangleShape rect;  // The rectangle shape of the text field
    sf::Font font;  // The font of the text
    u32 size;  // The maximum number of characters allowed in the text field
    bool hasfocus;  // Whether the text field is currently focused
    bool isWarning = false;  // Whether there is a warning
    float pressTime;  // The time since the last key press
    const float PRESS_DELAY = 0.4f;  // The delay between key presses
public:
    std::string warning;  // Warning message
    std::string instruction;  // Instruction message

    /**
     * Constructor that initializes the text field with a maximum number of characters and dimensions.
     */
    TextField(u32 maxChars, float width, float height);

    /**
     * Returns the text entered in the text field.
     */
    const std::string getText() const;

    /**
     * Sets the position of the text field.
     */
    void setPosition(float x, float y);

    /**
     * Checks if a point is within the text field.
     */
    bool contains(sf::Vector2f point) const;

    /**
     * Sets the focus of the text field.
     */
    void setFocus(bool focus);

    /**
     * Handles input events for the text field.
     */
    void handleInput(sf::Event event, float deltaTime);

    /**
     * Clears the text field.
     */
    void clear();

    /**
     * Draws the text field on a render target.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif

