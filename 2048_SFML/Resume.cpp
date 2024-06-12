#include "Resume.hpp"

Resume::Resume() : size(0), userNameField(), passwordField() {

	pressTime = PRESS_DELAY;

	if (!font.loadFromFile("Fonts/arial.ttf"))
		std::cout << "Could not load font\n";
	if (!backgroundTextureResume.loadFromFile("Texture/Resume.png"))
		std::cout << "Could not load background texture\n";
	backgroundResume.setTexture(backgroundTextureResume);
	backgroundResume.setPosition(0, 0);

	SELECT_BUTTON = 0;

	account1.setFont(font);
	account1.setCharacterSize(30);
	account1.setFillColor(sf::Color::Black);
	account1.setPosition(400, 350);

	account2.setFont(font);
	account2.setCharacterSize(30);
	account2.setFillColor(sf::Color::Black);
	account2.setPosition(400, 135);

	account3.setFont(font);
	account3.setCharacterSize(30);
	account3.setFillColor(sf::Color::Black);
	account3.setPosition(400, 170);

	account4.setFont(font);
	account4.setCharacterSize(30);
	account4.setFillColor(sf::Color::Black);
	account4.setPosition(400, 205);

	account5.setFont(font);
	account5.setCharacterSize(30);
	account5.setFillColor(sf::Color::Black);
	account5.setPosition(400, 240);

}

Player* Resume::getSelectedPlayer()
{
	return nullptr;
}

bool Resume::isMatchPassword()
{
	return false;
}

void Resume::handleInput(sf::Event event, sf::RenderWindow& window, Game::State state, float deltaTime)
{
	// Handle mouse button release event
	if (event.type == sf::Event::MouseButtonReleased) {
		auto pos = sf::Mouse::getPosition(window);
		if (passwordField.contains(sf::Vector2f(pos)))
			passwordField.setFocus(true);

	}
	// Handle text input event
	else if (event.type == sf::Event::TextEntered && state == Game::RESUME)
		passwordField.handleInput(event, deltaTime);
}

void Resume::addPlayer(std::string userName, u64 score, double timeToComplete, std::string password)
{
	
}

void Resume::addPlayer(Player player)
{
	
}

void Resume::update(float deltaTime)
{
	

}

void Resume::draw(sf::RenderWindow& window)
{
	if (state == Game::OPTION) {
		std::cout << "Resume4\n";
		window.draw(backgroundResume);
		if (account1.getString() != "")
			window.draw(account1);
		if (account2.getString() != "")
			window.draw(account2);
		if (account3.getString() != "")
			window.draw(account3);
		if (account4.getString() != "")
			window.draw(account4);
		if (account5.getString() != "")
			window.draw(account5);
	}
	else if (state == Game::RESUME_RESGISTER) {
		std::cout << "Resume5\n";
		window.draw(passwordField);
	}
	else if (state == Game::RESUME_PLAY_AGAIN) {
		std::cout << "Resume6\n";
		window.draw(passwordField);
	}
	else {
		std::cout << "Invalid state in resume\n";
	}
}

void Resume::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
