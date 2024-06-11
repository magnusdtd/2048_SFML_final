#ifndef Cell_HPP
#define Cell_HPP

#include <string.h>
#include <math.h>
#include "layout.hpp"
#include <iostream>

// Class representing a cell in the game board
class Cell : public sf::Drawable {
private:
    static sf::Font font; // The font used to display the cell's text
    sf::Text text; // The text displayed on the cell
    static sf::Texture texture; // The texture of the cell
    sf::Sprite sprite; // The sprite used to draw the cell

    // Method to update the cell's text and color
    void updateCell();
public:
    u64 value; // The value of the cell
    bool isNew = true; // Whether the cell is a new cell
    bool isMerged = false; // Whether the cell has been merged

    // Default constructor
    Cell();

    // Equality operator
    bool operator == (const Cell& c) const;

    // Assignment operator
    void operator = (const Cell& c);

    // Multiplication assignment operator
    void operator *= (const u64& val);

    // Initialize the cell
    void init(  float posX,
                float posY,
                sf::Font& font,
                float size,
                float alignX,
                float alignY,
                u32 sizeOfValue);

    // Set the value of the cell
    void setValue(u64 val);

    // Get the value of the cell
    u64 getValue() const;

    // Draw the cell
    virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};

#endif
