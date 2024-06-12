#include "Login.hpp"

Login::Login() :
    usernameField(20, 500.f, 36.f),
    passwordField(20, 500.f, 36.f)
{
    if (!backgroundTexture.loadFromFile("Texture/Login.png"))
        std::cout << "Cannot load texture for login background\n";
    background.setTexture(backgroundTexture);
    background.setPosition(300.f, 60.f);


    usernameField.setPosition(350.f, 364.f);
    usernameField.setFocus(true);
    usernameField.instruction = "Enter your name";
    usernameField.warning = "Name must only contain number \n0 - 9, letter A - Z, a - z, and NO space!!!";

    passwordField.setPosition(350.f, 550.f);
    passwordField.setHide(true);
    passwordField.instruction = "Enter password";
    passwordField.warning = "Password must only contain number \n0 - 9, letter A - Z, a - z, and NO space!!!";

	if (!font.loadFromFile("Fonts/arial.ttf"))
        std::cout << "Could not load font\n";

    alertText.setFont(font);
    alertText.setCharacterSize(40);
    alertText.setFillColor(sf::Color::Red);
    alertText.setPosition(454, 665);
    alertText.setString("Username exist!!!");
}

void Login::setWarning(bool warning)
{
    isWarning = warning;
}

void Login::handleInput(sf::Event event, sf::Vector2i position, Game::State state, float deltaTime) {
    // Handle mouse button release event
    if (event.type == sf::Event::MouseButtonReleased) {
        

        usernameField.setFocus(false);
        passwordField.setFocus(false);

        if (usernameField.contains(sf::Vector2f(position))) {
            usernameField.setFocus(true);
            passwordField.setFocus(false);
        }

        if (passwordField.contains(sf::Vector2f(position))) {
            passwordField.setFocus(true);
            usernameField.setFocus(false);
        }
    }
    // Handle text input event
    else if (event.type == sf::Event::TextEntered && state == Game::REGISTER) {
        usernameField.handleInput(event, deltaTime);
        passwordField.handleInput(event, deltaTime);
    }
}


std::string Login::getUsername() const {
    return usernameField.getText();
}

std::string Login::getPassword() const {
    return passwordField.getText();
}

void Login::clear()
{
    usernameField.clear();
	passwordField.clear();

    usernameField.setFocus(true);
    passwordField.setFocus(false);
}

void Login::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    if (isWarning)
        target.draw(alertText, states);
    usernameField.draw(target, states);
    passwordField.draw(target, states);
}