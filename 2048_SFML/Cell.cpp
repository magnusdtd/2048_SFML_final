#include "Cell.hpp"

sf::Texture Cell::texture;

void Cell::updateCell()
{
    text.setString(std::to_string(value));
    text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
    if (value == 0) {
        sprite.setColor(Color::colors[0]);
        text.setFillColor(Color::colors[0]);
    }
    else {
        sprite.setColor(Color::colors[(u64)log2(value)]);
        text.setFillColor(sf::Color::Black);
    }
}

// Default constructor
Cell::Cell() {
    value = 0;
    text.setFillColor(Color::colors[0]);
    text.setString(std::to_string(value));

    if (texture.getSize().x == 0) { // Load the texture only once
        texture.loadFromFile("Texture/tile.png");
    }
    sprite.setTexture(texture);
}

// Equality operator
bool Cell::operator==(const Cell& c) const {
    return value == c.value;
}

// Assignment operator
void Cell::operator=(const Cell& c) {
    value = c.value;
    this->updateCell();
}

// Multiplication assignment operator
void Cell::operator*=(const u64& val) {
    value *= val;
    text.setString(std::to_string(value));
    text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
    this->updateCell();
}

// Initialize the cell
void Cell::init(float posX,
    float posY,
    sf::Font& font,
    float size,
    float alignX,
    float alignY,
    u32 sizeOfValue)
{
    value = 0;

    text.setFont(font);
    text.setString(std::to_string(value));
    text.setCharacterSize(sizeOfValue);
    text.setPosition(posX + alignX, posY + alignY);
    text.setFillColor(Color::colors[0]);

    sprite.setScale(size / 75.f, size / 75.f);
    sprite.setColor(Color::colors[0]);
    sprite.setPosition(posX, posY);
}

// Set the value of the cell
void Cell::setValue(u64 val) {
    value = val;
    this->updateCell();
}

// Get the value of the cell
u64 Cell::getValue() const {
    return value;
}

// Draw the cell
void Cell::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    rt.draw(sprite, rs);
    rt.draw(text, rs);
}
