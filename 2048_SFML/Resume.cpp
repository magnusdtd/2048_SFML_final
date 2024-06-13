#include "Resume.hpp"

Resume::Resume() : 
	size(0),			passwordField(20, 500.f, 36.f),		security(),
	SELECT_BUTTON(0),	userSelected(0),					resumeList(),	
	isWarning(false),	pressTime(PRESS_DELAY),				state(Game::RESUME_OPTION),
	isNoAccount(false)
{
	if (!textFont.loadFromFile("Fonts/Arial.ttf"))
		std::cout << "Could not load Fonts/Arial.ttf\n";

	if (!titleFont.loadFromFile("Fonts/Heavitas.ttf"))
		std::cout << "Could not load Fonts/Heavitas.ttf\n";

	if (!backgroundTextureResume.loadFromFile("Texture/Resume.png"))
		std::cout << "Could not load background texture\n";
	backgroundResume.setTexture(backgroundTextureResume);
	backgroundResume.setPosition(0, 0);

	account1.setFont(textFont);
	account1.setCharacterSize(30);
	account1.setFillColor(sf::Color::Black);
	account1.setPosition(400, 350);

	account2.setFont(textFont);
	account2.setCharacterSize(30);
	account2.setFillColor(sf::Color::Black);
	account2.setPosition(400, 370);

	account3.setFont(textFont);
	account3.setCharacterSize(30);
	account3.setFillColor(sf::Color::Black);
	account3.setPosition(400, 390);

	account4.setFont(textFont);
	account4.setCharacterSize(30);
	account4.setFillColor(sf::Color::Black);
	account4.setPosition(400, 410);

	account5.setFont(textFont);
	account5.setCharacterSize(30);
	account5.setFillColor(sf::Color::Black);
	account5.setPosition(400, 430);


	if (!backgroundTextureResumeContinueLogin.loadFromFile("Texture/Login.png"))
		std::cout << "Could not load background texture\n";
	backgroundResumeLogin.setTexture(backgroundTextureResumeContinueLogin);
	backgroundResumeLogin.setPosition(300.f, 60.f);


	passwordField.setPosition(350.f, 550.f);
	passwordField.setHide(true);
	passwordField.instruction = "Enter password";
	passwordField.warning = "Password must only contain number \n0 - 9, letter A - Z, a - z, and NO space!!!";

	alertText.setFont(textFont);
	alertText.setCharacterSize(40);
	alertText.setFillColor(sf::Color::Red);
	alertText.setPosition(454, 665);
	alertText.setString("Username exist!!!");
}

ResumeNode* Resume::getSelectedResumeData()
{
	return resumeList.getData(userSelected);
}

void Resume::handleEvent(float deltaTime, sf::Event event, sf::Vector2i position)
{
	if (state == Game::RESUME_LOGIN) {
		if (event.type == sf::Event::MouseButtonReleased) {
			passwordField.setFocus(false);
			if (passwordField.contains(sf::Vector2f(position)))
				passwordField.setFocus(true);
		}
		else if (event.type == sf::Event::TextEntered)
			passwordField.handleInput(event, deltaTime);
	}
}

void Resume::addData(Player player, BoardStack boardStack, ScoreStack scoreStack)
{
	if (size == MAX_PLAYERS) {
		std::cout << "Resume is full\n";
		return;
	}
	resumeList.addData(player, boardStack, scoreStack);
	size++;
}

void Resume::saveData()
{
	resumeList.writeToFiles();
}

void Resume::loadData()
{
	resumeList.readFromFiles();
}

void Resume::clearData()
{
	resumeList.clearDataFiles();
}



void Resume::update(float deltaTime)
{
	pressTime -= deltaTime;
	if (state == Game::RESUME_OPTION) {

		ResumeNode* temp = resumeList.getData(0);
		if (temp != nullptr) {
			account1.setString("1. " + temp->getPlayer().getName());
			isNoAccount = false;
			temp = temp->next;
			size = 1;
		}
		else {
			account1.setString("No account to resume \npress E to turn back");
			isNoAccount = true;
			return;
		}

		if (temp != nullptr) {
			account2.setString("2. " + temp->getPlayer().getName());
			temp = temp->next;
			size = 2;
		}
		if (temp != nullptr) {
			account3.setString("3. " + temp->getPlayer().getName());
			temp = temp->next;
			size = 3;
		}
		if (temp != nullptr) {
			account4.setString("4. " + temp->getPlayer().getName());
			temp = temp->next;
			size = 4;
		}
		if (temp != nullptr) {
			account5.setString("5. " + temp->getPlayer().getName());
			temp = temp->next;
			size = 5;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			SELECT_BUTTON = (SELECT_BUTTON - 1 + size) % size;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			SELECT_BUTTON = (SELECT_BUTTON + 1 + size) % size;
		}

		switch (SELECT_BUTTON) {
		case 0:
			account1.setFillColor(sf::Color::Red);
			account2.setFillColor(sf::Color::Black);
			account3.setFillColor(sf::Color::Black);
			account4.setFillColor(sf::Color::Black);
			account5.setFillColor(sf::Color::Black);
			break;
		case 1:
			account1.setFillColor(sf::Color::Black);
			account2.setFillColor(sf::Color::Red);
			account3.setFillColor(sf::Color::Black);
			account4.setFillColor(sf::Color::Black);
			account5.setFillColor(sf::Color::Black);
			break;
		case 2:
			account1.setFillColor(sf::Color::Black);
			account2.setFillColor(sf::Color::Black);
			account3.setFillColor(sf::Color::Red);
			account4.setFillColor(sf::Color::Black);
			account5.setFillColor(sf::Color::Black);
			break;
		case 3:
			account1.setFillColor(sf::Color::Black);
			account2.setFillColor(sf::Color::Black);
			account3.setFillColor(sf::Color::Black);
			account4.setFillColor(sf::Color::Red);
			account5.setFillColor(sf::Color::Black);
			break;
		case 4:
			account1.setFillColor(sf::Color::Black);
			account2.setFillColor(sf::Color::Black);
			account3.setFillColor(sf::Color::Black);
			account4.setFillColor(sf::Color::Black);
			account5.setFillColor(sf::Color::Red);
			break;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			state = Game::RESUME_GO_BACK;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pressTime + 0.7f <= 0.f) {
			pressTime = PRESS_DELAY;
			state = Game::RESUME_LOGIN;
			switch (SELECT_BUTTON) {
			case 0:
				userSelected = 0;
				break;
			case 1:
				userSelected = 1;
				break;
			case 2:
				userSelected = 2;
				break;
			case 3:
				userSelected = 3;
				break;
			}

		}
	} 
	else if (state == Game::RESUME_LOGIN) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
			passwordField.getText() == resumeList.getData(userSelected)->getPlayer().getPassword() &&
			pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			state = Game::RESUME_PLAY;
			passwordField.clear();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && passwordField.getText() != "" && pressTime <= 0.f) {
			alertText.setString("Wrong password!!!");
			isWarning = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			state = Game::RESUME_OPTION;
		}
	} 
	else if (state == Game::RESUME_PLAY) {
		std::cout << "This is resume play\n";
	}
	else if (state == Game::RESUME_GO_BACK) {
		
	}
	else
		std::cout << "Invalid state in Resume\n";
}

void Resume::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (state == Game::RESUME_OPTION) {
		target.draw(backgroundResume, states);
		if (account1.getString() != "1. ")
			target.draw(account1, states);
		if (account2.getString() != "2. ")
			target.draw(account2, states);
		if (account3.getString() != "3. ")
			target.draw(account3, states);
		if (account4.getString() != "4. ")
			target.draw(account4, states);
		if (account5.getString() != "5. ")
			target.draw(account5, states);
	}
	else if (state == Game::RESUME_LOGIN) {
		target.draw(backgroundResumeLogin, states);
		target.draw(passwordField, states);

		if (isWarning)
			target.draw(alertText, states);
	}
	else if (state == Game::RESUME_PLAY) {
		// Play the game
	}
	else if (state == Game::RESUME_GO_BACK) {
		// Go back to the main menu
	}
	else
		std::cout << "Invalid state in Resume\n";
}
