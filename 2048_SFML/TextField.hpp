#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class TextField : public sf::Drawable, public sf::Transformable {
private:
    std::string text;
    sf::RectangleShape rect;
    sf::Font font;
    unsigned int size;
    bool hasfocus;
public:
    TextField(unsigned int maxChars, float width, float height);
    const std::string getText() const;
    void setPosition(float x, float y);
    bool contains(sf::Vector2f point) const;
    void setFocus(bool focus);
    void handleInput(sf::Event e);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif

