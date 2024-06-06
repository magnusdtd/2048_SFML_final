#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class TextField : public sf::Drawable, public sf::Transformable {
private:
    std::string text;
    std::string warnning;
    std::string instruction;
    sf::RectangleShape rect;
    sf::Font font;
    unsigned int size;
    bool hasfocus;
    bool isWarnning = false;
    float pressTime;
    const float PRESS_DELAY = 0.4f;
public:
    TextField(unsigned int maxChars, float width, float height);
    const std::string getText() const;
    void setPosition(float x, float y);
    bool contains(sf::Vector2f point) const;
    void setFocus(bool focus);
    void handleInput(sf::Event event, float deltaTime);
    void clear();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif

