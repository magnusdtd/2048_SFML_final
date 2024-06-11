#include "Cell.hpp"

sf::Texture Cell::texture;
sf::Font Cell::font;

void Cell::updateCell()
{
    text.setString(std::to_string(value));
    text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
    if (value == 0) {
        sprite.setColor(Color::colors[0]);
        text.setFillColor(Color::colors[0]);
    }
    else {
        sprite.setColor(Color::colors[((u64)log2(value)) % 12]);
        text.setFillColor(sf::Color::Black);
    }

}

// Default constructor
Cell::Cell() : value(0) {
    if (font.getInfo().family == "") { // Load the font only once (static member
        font.loadFromFile("Fonts/font.ttf");
        std::cout << "Check font for one cell\n";
    }
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
void Cell::operator *= (const u64& val) {
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
                u32 sizeOfValue,
                float alignNewText,
                u32 sizeOfNewText)
{
    value = 0;
    this->alignNewText = alignNewText;
    this->sizeOfNewText = sizeOfNewText;

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
void Cell::draw(sf::RenderTarget& rt, sf::RenderStates rs) const{
    rt.draw(sprite, rs);
    rt.draw(text, rs);

    if(isNew) {
        sf::Text newText;
        newText.setFont(font);
        newText.setString("New");
        newText.setCharacterSize(sizeOfNewText);
        newText.setFillColor(sf::Color(Random<u32>(0, 255), Random<u32>(0, 255), Random<u32>(0, 255)));
        newText.setPosition(sprite.getPosition().x + alignNewText, sprite.getPosition().y + alignNewText);
        rt.draw(newText, rs);
	}
}
