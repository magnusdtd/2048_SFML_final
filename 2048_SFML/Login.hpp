#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "TextField.hpp"
#include "layout.hpp"
#include <SFML/Graphics.hpp>

class Login : public sf::Drawable {
private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    TextField usernameField;
    TextField passwordField;

    sf::Font font;
    sf::Text alertText;
    bool isWarning = false;
public:
    Login();

    void setWarning(bool warning);

    void handleInput(sf::Event event, sf::Vector2i position, Game::State state, float deltaTime);

    std::string getUsername() const;

    std::string getPassword() const;

    void clear();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
