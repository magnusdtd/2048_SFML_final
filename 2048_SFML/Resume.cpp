#include "Resume.hpp"

Resume::Resume() : size(0), usernameField(), passwordField(), head(nullptr), boardData(nullptr) {

	pressTime = PRESS_DELAY;

	if (!textFont.loadFromFile("Fonts/Arial.ttf"))
		std::cout << "Could not load Fonts/Arial.ttf\n";

	if (!titleFont.loadFromFile("Fonts/Heavitas.ttf"))
		std::cout << "Could not load Fonts/Heavitas.ttf\n";

	if (!backgroundTextureResume.loadFromFile("Texture/Resume.png"))
		std::cout << "Could not load background texture\n";
	backgroundResume.setTexture(backgroundTextureResume);
	backgroundResume.setPosition(0, 0);

	SELECT_BUTTON = 0;

	account1.setFont(textFont);
	account1.setCharacterSize(30);
	account1.setFillColor(sf::Color::Black);
	account1.setPosition(400, 350);

	account2.setFont(textFont);
	account2.setCharacterSize(30);
	account2.setFillColor(sf::Color::Black);
	account2.setPosition(400, 135);

	account3.setFont(textFont);
	account3.setCharacterSize(30);
	account3.setFillColor(sf::Color::Black);
	account3.setPosition(400, 170);

	account4.setFont(textFont);
	account4.setCharacterSize(30);
	account4.setFillColor(sf::Color::Black);
	account4.setPosition(400, 205);

	account5.setFont(textFont);
	account5.setCharacterSize(30);
	account5.setFillColor(sf::Color::Black);
	account5.setPosition(400, 240);


	resumeOption1.setFont(titleFont);
	resumeOption1.setCharacterSize(50);
	resumeOption1.setFillColor(sf::Color::Red);
	resumeOption1.setPosition(400, 350);
	resumeOption1.setString("New account");

	resumeOption2.setFont(titleFont);
	resumeOption2.setCharacterSize(50);
	resumeOption2.setFillColor(sf::Color::Black);
	resumeOption2.setPosition(450, 410);
	resumeOption2.setString("Continue");

	if (!backgroundTextureResumeContinueLogin.loadFromFile("Texture/Login.png"))
		std::cout << "Could not load background texture\n";
	backgroundResumeContinueLogin.setTexture(backgroundTextureResumeContinueLogin);
	backgroundResumeContinueLogin.setPosition(0, 0);

	usernameField.setPosition(350.f, 364.f);
	usernameField.setFocus(true);
	usernameField.instruction = "Enter your name";
	usernameField.warning = "Name must only contain number \n0 - 9, letter A - Z, a - z, and NO space!!!";

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

Resume::~Resume()
{
	ResumeData* temp = head;
	while (temp != nullptr) {
		ResumeData* next = temp->next;
		delete temp;
		temp = next;
		size--;
	}
}

void Resume::handleEvent(float deltaTime, sf::Event event, sf::Vector2i position)
{
	if (state == Game::RESUME_CONTINUE_LOGIN) {
		if (event.type == sf::Event::MouseButtonReleased) {
			usernameField.setFocus(false);
			if (passwordField.contains(sf::Vector2f(position)))
				passwordField.setFocus(true);
		}
		else if (event.type == sf::Event::TextEntered)
			passwordField.handleInput(event, deltaTime);
	}
	else if (state == Game::RESUME_REGISTER) {
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
		else if (event.type == sf::Event::TextEntered) {
			usernameField.handleInput(event, deltaTime);
			passwordField.handleInput(event, deltaTime);
		}
	}
}

void Resume::addData(Player player, u64** board)
{
	ResumeData* temp = head;

	u64* tempBoard = new u64[size * size];
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			tempBoard[i * size + j] = board[i][j];

	if (temp == nullptr) {
		head = new ResumeData(player, tempBoard);
		size++;
		return;
	}

	while (temp->next != nullptr)
		temp = temp->next;

	temp->next = new ResumeData(player, tempBoard);
	size++;
}


void Resume::update(float deltaTime)
{
	pressTime -= deltaTime;
	if (state == Game::RESUME_OPTION) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			if (SELECT_BUTTON > 0)
				SELECT_BUTTON--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			if (SELECT_BUTTON < 1)
				SELECT_BUTTON++;
		}

		if (SELECT_BUTTON == 0) {
			resumeOption1.setFillColor(sf::Color::Red);
			resumeOption2.setFillColor(sf::Color::Black);
		}
		else {
			resumeOption1.setFillColor(sf::Color::Black);
			resumeOption2.setFillColor(sf::Color::Red);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pressTime <= 0.f)
			if (SELECT_BUTTON == 0) // Add or remove player
				state = Game::RESUME_REGISTER;
			else // Continue the game SELECT_BUTTON == 1
				state = Game::RESUME_CONTINUE;
	} 
	else if (state == Game::RESUME_REGISTER) {

		ResumeData* temp = head;
		if (temp != nullptr) {
			account1.setString("1. " + temp->getPlayer().getName());
			temp = temp->next;
		}
		if (temp != nullptr) {
			account2.setString("2. " + temp->getPlayer().getName());
			temp = temp->next;
		}
		if (temp != nullptr) {
			account3.setString("3. " + temp->getPlayer().getName());
			temp = temp->next;
		}
		if (temp != nullptr) {
			account4.setString("4. " + temp->getPlayer().getName());
			temp = temp->next;
		}
		if (temp != nullptr) {
			account5.setString("5. " + temp->getPlayer().getName());
			temp = temp->next;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			if (SELECT_BUTTON > 0)
				SELECT_BUTTON--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			if (SELECT_BUTTON < 4)
				SELECT_BUTTON++;
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
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			if (SELECT_BUTTON == 0) {
				
			}
			else if (SELECT_BUTTON == 1) {
				
			}
			else if (SELECT_BUTTON == 2) {
				
			}
			else if (SELECT_BUTTON == 3) {
				
			}
			else if (SELECT_BUTTON == 4) {
				
			}
		}



		std::cout << "This is the resume register\n";
	} 
	else if (state == Game::RESUME_CONTINUE) {
		ResumeData* temp = head;
		if (temp != nullptr) {
			account1.setString("1. " + temp->getPlayer().getName());
			temp = temp->next;
		}
		else {
			account1.setString("No account to resume \npress E to turn back");

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && pressTime <= 0.f) {
				pressTime = PRESS_DELAY;
				state = Game::RESUME_OPTION;
			}

			return;
		}
		if (temp != nullptr) {
			account2.setString("2. " + temp->getPlayer().getName());
			temp = temp->next;
		}
		if (temp != nullptr) {
			account3.setString("3. " + temp->getPlayer().getName());
			temp = temp->next;
		}
		if (temp != nullptr) {
			account4.setString("4. " + temp->getPlayer().getName());
			temp = temp->next;
		}
		if (temp != nullptr) {
			account5.setString("5. " + temp->getPlayer().getName());
			temp = temp->next;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			if (SELECT_BUTTON > 0)
				SELECT_BUTTON--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			if (SELECT_BUTTON < size)
				SELECT_BUTTON++;
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			temp = head; s32 cnt = (s32)SELECT_BUTTON;
			while (temp != nullptr && cnt > 0)
				temp = temp->next;

			if (temp != nullptr) {
				u64* tempBoard = temp->getBoard();
				this->boardData = new u64 * [size];
				for (u32 i = 0; i < size; i++) {
					this->boardData[i] = new u64[size];
					for (u32 j = 0; j < size; j++) {
						this->boardData[i][j] = tempBoard[i * size + j];
					}
				}

				state = Game::RESUME_CONTINUE_LOGIN;
			}


		}
	} 
	else if (state == Game::RESUME_CONTINUE_LOGIN) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && 
			passwordField.getText() == currentPlayer.getPassword() &&
			pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			state = Game::RESUME_PLAY;
		}
		else {
			alertText.setString("Wrong password!!!");
			isWarning = true;
		}

	}
	else
		std::cout << "Invalid state in Resume\n";
}

void Resume::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (state == Game::RESUME_OPTION) {
		target.draw(backgroundResume, states);
		target.draw(resumeOption1, states);
		target.draw(resumeOption2, states);
	}
	else if (state == Game::RESUME_CHOOSE_ACCOUNT) {
		target.draw(backgroundResume, states);
		if (account1.getString() != "")
			target.draw(account1, states);
		if (account2.getString() != "")
			target.draw(account2, states);
		if (account3.getString() != "")
			target.draw(account3, states);
		if (account4.getString() != "")
			target.draw(account4, states);
		if (account5.getString() != "")
			target.draw(account5, states);
	}
	else if (state == Game::RESUME_REGISTER) {
		target.draw(backgroundResumeContinueLogin, states);
		target.draw(passwordField, states);
		target.draw(usernameField, states);
	}
	else if (state == Game::RESUME_CONTINUE) {
		target.draw(backgroundResume, states);
		if (account1.getString() != "")
			target.draw(account1, states);
		if (account2.getString() != "")
			target.draw(account2, states);
		if (account3.getString() != "")
			target.draw(account3, states);
		if (account4.getString() != "")
			target.draw(account4, states);
		if (account5.getString() != "")
			target.draw(account5, states);
	}
	else if (state == Game::RESUME_CONTINUE_LOGIN) {
		target.draw(backgroundResumeContinueLogin, states);
		target.draw(passwordField, states);

		if (isWarning)
			target.draw(alertText, states);
	}
	else if (state == Game::RESUME_PLAY) {
		// Play the game
	}
	else
		std::cout << "Invalid state in Resume 2\n";
}
