#include "Resume.hpp"

Resume::Resume()
	: PlayerList(), userNameField(), passwordField() {
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
	std::string password = passwordField.getText();
	Player *temp = PlayerList::getPlayer(opt.getString());\
	if (temp != nullptr && temp->getPassword() == password)
		return true;
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
	if (size < MAX_PLAYERS)
		PlayerList::addPlayer(userName, score, timeToComplete, password);
	else
		std::cout << "Maximum number of players reached. Cannot add more.\n";
}

void Resume::addPlayer(Player player)
{
	if (size < MAX_PLAYERS)
		PlayerList::addPlayer(player);
	else
		std::cout << "Maximum number of players reached. Cannot add more.\n";
}

void Resume::update(float deltaTime)
{
	pressTime -= deltaTime;

	if (state == Game::OPTION) {
		if (size != 0) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.f) {
				pressTime = PRESS_DELAY;
				SELECT_BUTTON = (SELECT_BUTTON + 1) % size;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.f) {
				pressTime = PRESS_DELAY;
				SELECT_BUTTON = (SELECT_BUTTON - 1 + size) % size;
			}

			if (size >= MAX_PLAYERS) {
				switch (SELECT_BUTTON) {
				case 0:
					account1.setFillColor(sf::Color::Red);
					account2.setFillColor(sf::Color::Black);
					account3.setFillColor(sf::Color::Black);
					account4.setFillColor(sf::Color::Black);
					account5.setFillColor(sf::Color::Black);
					opt = account1;
					break;
				case 1:
					account1.setFillColor(sf::Color::Black);
					account2.setFillColor(sf::Color::Red);
					account3.setFillColor(sf::Color::Black);
					account4.setFillColor(sf::Color::Black);
					account5.setFillColor(sf::Color::Black);
					opt = account2;
					break;
				case 2:
					account1.setFillColor(sf::Color::Black);
					account2.setFillColor(sf::Color::Black);
					account3.setFillColor(sf::Color::Red);
					account4.setFillColor(sf::Color::Black);
					account5.setFillColor(sf::Color::Black);
					opt = account3;
					break;
				case 3:
					account1.setFillColor(sf::Color::Black);
					account2.setFillColor(sf::Color::Black);
					account3.setFillColor(sf::Color::Black);
					account4.setFillColor(sf::Color::Red);
					account5.setFillColor(sf::Color::Black);
					opt = account4;
					break;
				case 4:
					account1.setFillColor(sf::Color::Black);
					account2.setFillColor(sf::Color::Black);
					account3.setFillColor(sf::Color::Black);
					account4.setFillColor(sf::Color::Black);
					account5.setFillColor(sf::Color::Red);
					opt = account5;
					break;
				default:
					std::cout << "Invalid selection in resume\n";
				}
			}

			Player* temp = this->head;
			if (temp != nullptr) {
				account1.setString("1. Player: " + temp->getName() + "");
				temp = temp->next;
			}
			if (temp != nullptr) {
				account2.setString("2. Player: " + temp->getName() + "");
				temp = temp->next;
			}
			if (temp != nullptr) {
				account3.setString("3. Player: " + temp->getName() + "");
				temp = temp->next;
			}
			if (temp != nullptr) {
				account4.setString("4. Player: " + temp->getName() + "");
				temp = temp->next;
			}
			if (temp != nullptr) {
				account5.setString("5. Player: " + temp->getName() + "");
				temp = temp->next;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pressTime <= 0.f) {
				pressTime = PRESS_DELAY;
				state = Game::RESUME_RESGISTER;
			}
		}
		else {
			account1.setString("No account for resume");
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pressTime <= 0.f) {
				pressTime = PRESS_DELAY;
				state = Game::RESUME_PLAY_AGAIN;
			}
		}

	}
	else if (state == Game::RESUME_RESGISTER) { // The scenario that there are not enough 5 account in the resume list
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
			userNameField.getText().size() != 0 && 
			passwordField.getText().size() != 0 &&
			pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			state = Game::OPTION;
		}
	}
	else if (state == Game::RESUME_PLAY_AGAIN) { // The scenario that there are 5 account in the resume list
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
			passwordField.getText().size() != 0 &&
			this->isMatchPassword() &&
			pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			state = Game::OPTION;
		}
	}
	else
		std::cout << "Invalid state in resume\n";

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
