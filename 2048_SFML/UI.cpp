#include "UI.hpp"

/**
 * Constructor for the UI class.
 * Initializes the UI elements.
 */
UI::UI() {
	/* Common */
	if (!font.loadFromFile("Fonts/font.ttf"))
		std::cout << "Error loading font\n";
	state = Game::START_MENU;
	pressTime = 0.f;

	/* Start Menu */
	// Initialize start menu elements...
	backgroundTextureStartMenu.loadFromFile("Texture/StartMenu.png");
	backgroundStartMenu.setTexture(backgroundTextureStartMenu);
	SELECT_BUTTON = Game::StartMenuButton::NewGame;

	ButtonNewGame.setFont(font);
	ButtonNewGame.setString("New Game");
	ButtonNewGame.setCharacterSize(32);
	ButtonNewGame.setFillColor(sf::Color(0, 0, 0));
	ButtonNewGame.setPosition(Game::GAME_WIDTH / 2.f - 100.f, Game::GAME_HEIGHT / 2.f + 60.f);

	ButtonSetting.setFont(font);
	ButtonSetting.setString("Setting");
	ButtonSetting.setCharacterSize(32);
	ButtonSetting.setFillColor(sf::Color(0, 0, 0));
	ButtonSetting.setPosition(Game::GAME_WIDTH / 2.f - 100.f, Game::GAME_HEIGHT / 2.f + 120.f);

	ButtonTop20List.setFont(font);
	ButtonTop20List.setString("Top 20 List");
	ButtonTop20List.setCharacterSize(32);
	ButtonTop20List.setFillColor(sf::Color(0, 0, 0));
	ButtonTop20List.setPosition(Game::GAME_WIDTH / 2.f - 100.f, Game::GAME_HEIGHT / 2.f + 180.f);

	ButtonResume.setFont(font);
	ButtonResume.setString("Resume");
	ButtonResume.setCharacterSize(32);
	ButtonResume.setFillColor(sf::Color(0, 0, 0));
	ButtonResume.setPosition(Game::GAME_WIDTH / 2.f - 100.f, Game::GAME_HEIGHT / 2.f + 240.f);

	/* Setting */
    // Initialize setting elements...
	backgroundTextureSetting.loadFromFile("Texture/Setting.png");
	backgroundSetting.setTexture(backgroundTextureSetting);

	whichButton = 0;

	mode = Game::MODE_4; // Default mode
	textMode.setFont(font);
	textMode.setString(std::to_string(mode));
	textMode.setCharacterSize(64);
	textMode.setFillColor(sf::Color(0, 0, 0));
	textMode.setPosition(816.f, 342.f);

	textOnOff.setFont(font);
	textOnOff.setString("Off"); // Default for Undo/Redo function
	textOnOff.setCharacterSize(64);
	textOnOff.setFillColor(sf::Color(0, 0, 0));
	textOnOff.setPosition(829.f, 518.f);

	buttonOnOff = 0;
	buttonMode = 0;


	/* Playing*/
	// Initialize playing and register elements...
	backgroundTexturePlaying.loadFromFile("Texture/background.png");
	backgroundPlaying.setTexture(backgroundTexturePlaying);
	
	bestScore = this->loadBestScore("Data/best_score.dat");
	textBestScore.setFont(font);
	textBestScore.setString(std::to_string(bestScore));
	textBestScore.setCharacterSize(32);
	textBestScore.setFillColor(sf::Color(0, 0, 0));
	textBestScore.setPosition(1010.f, 365.f);
	textBestScore.setOrigin(textBestScore.getGlobalBounds().width / 2, textBestScore.getGlobalBounds().height / 2);

	textScore.setFont(font);
	textScore.setString(std::to_string(score));
	textScore.setCharacterSize(32);
	textScore.setFillColor(sf::Color(0, 0, 0));
	textScore.setPosition(1010.f, 580.f);
	textScore.setOrigin(textScore.getGlobalBounds().width / 2, textScore.getGlobalBounds().height / 2);

	textGameOver.setFont(font);
	textGameOver.setCharacterSize(60);
	textGameOver.setFillColor(sf::Color(204, 0, 0));
	textGameOver.setPosition(650, 370);

	textWin.setFont(font);
	textWin.setCharacterSize(60);
	textWin.setFillColor(sf::Color(204, 0, 0));
	textWin.setPosition(650, 370);

	subMessage.setFont(font);
	subMessage.setCharacterSize(20);
	subMessage.setFillColor(sf::Color(204, 0, 0));
	subMessage.setPosition(650, 500);
}

Player UI::getPlayer() const
{
	return player;
}

/**
 * Returns the current game state.
 * @return Current game state
 */
Game::State UI::getState() const
{
	return state;
}

/**
* Loads the best score from a file.
*/
u64 UI::loadBestScore(std::string filename)
{
	// Open the file in binary mode for reading.
	std::ifstream input(filename, std::ios::binary | std::ios::in);
	u64 bestScore = 0;

	// If the file is open, read the best score from it.
	if (input.is_open()) {
		input.read(reinterpret_cast<char*>(&bestScore), sizeof(u64));
		input.close();
	}
	else
		// If the file could not be opened, print an error message.
		std::cerr << "Unable to open file: " << filename << std::endl;

	// Return the best score.
	return bestScore;
}

/**
* Saves the best score to a file.
*/
void UI::saveBestScore(std::string filename) const
{
	// Open the file in binary mode for writing.
	std::ofstream output(filename, std::ios::binary);

	// If the file is open, write the score to it.
	if (output.is_open()) {
		output.write(reinterpret_cast<const char*>(&bestScore), sizeof(u64));
		output.close();
	}
	else
		// If the file could not be opened, print an error message.
		std::cerr << "Unable to open file: " << filename << std::endl;
}


/**
 * Handles the game over state.
 * Checks if a new score has been achieved and saves it if necessary.
 */
void UI::GameOverMessage(u64 position) {
	isGameOver = true;
	if (position <= 20)
		textGameOver.setString("Game Over\nYou reach top " + std::to_string(position));
	else
		textGameOver.setString("Game Over\nYou can't reach top 20");
	subMessage.setString("Press E to back to the main menu\n or press C to continue");
}

void UI::WinMessage(u64 position)
{
	isWin = true;
	if (position <= 20)
		textWin.setString("You Win\nYou reach top " + std::to_string(position));
	else
		textWin.setString("You Win\nYou can't reach top 20");
	subMessage.setString("Press E to back to the main menu\n or press C to continue");
}

/**
 * Updates the UI based on the current game state.
 * @param deltaTime Time since the last frame
 * @param board Reference to the game board
 * @param tf Reference to the text field
 */
void UI::update(float deltaTime, Board& board, Login& login, PlayerList& playerList, Resume& resume) {
	// Update UI based on the current game state...
	pressTime -= deltaTime;
	if (state == Game::START_MENU) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.f) {
			(SELECT_BUTTON += (Game::NUMBER_OF_BUTTONS - 1)) %= Game::NUMBER_OF_BUTTONS;
			pressTime = PRESS_DELAY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.f) {
			(SELECT_BUTTON += (Game::NUMBER_OF_BUTTONS + 1)) %= Game::NUMBER_OF_BUTTONS;
			pressTime = PRESS_DELAY;
		}

		switch (SELECT_BUTTON) {
		case Game::StartMenuButton::NewGame:
			ButtonNewGame.setFillColor(sf::Color(255, 0, 0));
			ButtonSetting.setFillColor(sf::Color(0, 0, 0));
			ButtonTop20List.setFillColor(sf::Color(0, 0, 0));
			ButtonResume.setFillColor(sf::Color(0, 0, 0));
			break;
		case Game::StartMenuButton::Setting:
			ButtonNewGame.setFillColor(sf::Color(0, 0, 0));
			ButtonSetting.setFillColor(sf::Color(255, 0, 0));
			ButtonTop20List.setFillColor(sf::Color(0, 0, 0));
			ButtonResume.setFillColor(sf::Color(0, 0, 0));
			break;
		case Game::StartMenuButton::Top20List:
			ButtonNewGame.setFillColor(sf::Color(0, 0, 0));
			ButtonSetting.setFillColor(sf::Color(0, 0, 0));
			ButtonTop20List.setFillColor(sf::Color(255, 0, 0));
			ButtonResume.setFillColor(sf::Color(0, 0, 0));
			break;
		case Game::StartMenuButton::Resume:
			ButtonNewGame.setFillColor(sf::Color(0, 0, 0));
			ButtonSetting.setFillColor(sf::Color(0, 0, 0));
			ButtonTop20List.setFillColor(sf::Color(0, 0, 0));
			ButtonResume.setFillColor(sf::Color(255, 0, 0));
			break;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			if (SELECT_BUTTON == Game::NewGame)
				state = Game::REGISTER;
			else if (SELECT_BUTTON == Game::Setting)
				state = Game::SETTING;
			else if (SELECT_BUTTON == Game::Top20List)
				state = Game::TOP20LIST;
			else if (SELECT_BUTTON == Game::Resume)
				state = Game::RESUME;

	}
	else if (state == Game::SETTING) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pressTime <= 0.f) {
			whichButton = (whichButton + 1) % 2;
			pressTime = PRESS_DELAY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pressTime <= 0.f) {
			whichButton = (whichButton + 1) % 2;
			pressTime = PRESS_DELAY;
		}

		if (whichButton) { // whichButton == 1 => Choose turn on Undo/Redo
			textOnOff.setFillColor(sf::Color(255, 0, 0));
			textMode.setFillColor(sf::Color(0, 0, 0));
		}
		else {
			textMode.setFillColor(sf::Color(255, 0, 0));
			textOnOff.setFillColor(sf::Color(0, 0, 0));
		}

		// Button on/off
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && whichButton && pressTime <= 0.f) {
			buttonOnOff = (buttonOnOff + 1) % 2;
			pressTime = PRESS_DELAY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && whichButton && pressTime <= 0.f) {
			buttonOnOff = (buttonOnOff + 1) % 2;
			pressTime = PRESS_DELAY;
		}
		// Button mode
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !whichButton && pressTime <= 0.f) {
			buttonMode = (buttonMode + 6) % 7;
			pressTime = PRESS_DELAY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !whichButton && pressTime <= 0.f) {
			buttonMode = (buttonMode + 1) % 7;
			pressTime = PRESS_DELAY;
		}

		textOnOff.setString((buttonOnOff) ? "On" : "Off");
		board.OnOffStack = (buttonOnOff == 1) ? true : false;

		switch (buttonMode) {
		case 0:
			textMode.setString("4");
			mode = Game::MODE_4;
			break;
		case 1:
			textMode.setString("5");
			mode = Game::MODE_5;
			break;
		case 2:
			textMode.setString("6");
			mode = Game::MODE_6;
			break;
		case 3:
			textMode.setString("7");
			mode = Game::MODE_7;
			break;
		case 4:
			textMode.setString("8");
			mode = Game::MODE_8;
			break;
		case 5:
			textMode.setString("9");
			mode = Game::MODE_9;
			break;
		case 6:
			textMode.setString("10");
			mode = Game::MODE_10;
			break;
		}
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			state = Game::START_MENU;
		}
	}
	else if (state == Game::TOP20LIST) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			state = Game::START_MENU;
	}
	else if (state == Game::RESUME) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && 
			(resume.getState() == Game::RESUME_RESGISTER || resume.getState() == Game::RESUME_PLAY_AGAIN) &&
			resume.isMatchPassword() &&
			pressTime + 1.f <= 0.f) {
			pressTime = PRESS_DELAY;
			state = Game::PLAYING;
			///* Copy player form resume list to */
			//if (resume.getState() == Game::RESUME_RESGISTER) {
			//	// The scenario that there are not enough 5 account in the resume list
			//	Player *temp = resume.getSelectedPlayer();
			//	player.setUserName(temp->getName());
			//	player.setPassword(temp->getPassword());
			//	player.setScore(temp->getScore());

			//}
			//else if (resume.getState() == Game::RESUME_PLAY_AGAIN) {
			//	// The scenario that there are enough 5 account in the resume list
			//	Player* temp = resume.getSelectedPlayer();
			//	player.setUserName(temp->getName());
			//	player.setPassword(temp->getPassword());
			//	player.setScore(temp->getScore());
			//	//startTime += std::chrono::seconds(temp->getTime());
			//}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && pressTime <= 0.f) {
			pressTime = PRESS_DELAY;
			state = Game::START_MENU;
		}
	}
	else if (state == Game::REGISTER) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && 
			login.getUsername().size() != 0 &&
			login.getPassword().size() != 0 && 
			!playerList.findPlayer(login.getUsername()) &&
			pressTime + 2.f <= 0.0f) {

			pressTime = PRESS_DELAY;
			state = Game::PLAYING;
			switch (mode) {
			case Game::MODE_4:
				board.init(	Game::GAME_WIDTH,
							Game::GAME_HEIGHT,
							LAYOUT::LAYOUT_4.boardSize,
							LAYOUT::LAYOUT_4.sizeOfEachCell,
							LAYOUT::LAYOUT_4.distanceBetweenEachCell,
							LAYOUT::LAYOUT_4.distanceBetweenCellAndBorder,
							LAYOUT::LAYOUT_4.alignX,
							LAYOUT::LAYOUT_4.alignY,
							LAYOUT::LAYOUT_4.sizeOfValue, 
							LAYOUT::LAYOUT_4.alignNextText, 
							LAYOUT::LAYOUT_4.sizeOfNextText );
				break;
			case Game::MODE_5:
				board.init(	Game::GAME_WIDTH,
							Game::GAME_HEIGHT,
							LAYOUT::LAYOUT_5.boardSize,
							LAYOUT::LAYOUT_5.sizeOfEachCell,
							LAYOUT::LAYOUT_5.distanceBetweenEachCell,
							LAYOUT::LAYOUT_5.distanceBetweenCellAndBorder,
							LAYOUT::LAYOUT_5.alignX,
							LAYOUT::LAYOUT_5.alignY,
							LAYOUT::LAYOUT_5.sizeOfValue,
							LAYOUT::LAYOUT_5.alignNextText,
							LAYOUT::LAYOUT_5.sizeOfNextText);
				break;
			case Game::MODE_6:
				board.init(	Game::GAME_WIDTH,
							Game::GAME_HEIGHT,
							LAYOUT::LAYOUT_6.boardSize,
							LAYOUT::LAYOUT_6.sizeOfEachCell,
							LAYOUT::LAYOUT_6.distanceBetweenEachCell,
							LAYOUT::LAYOUT_6.distanceBetweenCellAndBorder,
							LAYOUT::LAYOUT_6.alignX,
							LAYOUT::LAYOUT_6.alignY,
							LAYOUT::LAYOUT_6.sizeOfValue, 
							LAYOUT::LAYOUT_6.alignNextText,
							LAYOUT::LAYOUT_6.sizeOfNextText);
				break;
			case Game::MODE_7:
				board.init(	Game::GAME_WIDTH,
							Game::GAME_HEIGHT,
							LAYOUT::LAYOUT_7.boardSize,
							LAYOUT::LAYOUT_7.sizeOfEachCell,
							LAYOUT::LAYOUT_7.distanceBetweenEachCell,
							LAYOUT::LAYOUT_7.distanceBetweenCellAndBorder,
							LAYOUT::LAYOUT_7.alignX,
							LAYOUT::LAYOUT_7.alignY,
							LAYOUT::LAYOUT_7.sizeOfValue, 
							LAYOUT::LAYOUT_7.alignNextText,
							LAYOUT::LAYOUT_7.sizeOfNextText);
						break;
			case Game::MODE_8:
				board.init(	Game::GAME_WIDTH,
							Game::GAME_HEIGHT,
							LAYOUT::LAYOUT_8.boardSize,
							LAYOUT::LAYOUT_8.sizeOfEachCell,
							LAYOUT::LAYOUT_8.distanceBetweenEachCell,
							LAYOUT::LAYOUT_8.distanceBetweenCellAndBorder, 
							LAYOUT::LAYOUT_8.alignX,
							LAYOUT::LAYOUT_8.alignY,
							LAYOUT::LAYOUT_8.sizeOfValue, 
							LAYOUT::LAYOUT_8.alignNextText,
							LAYOUT::LAYOUT_8.sizeOfNextText);
				break;
			case Game::MODE_9:
				board.init(	Game::GAME_WIDTH,
							Game::GAME_HEIGHT,
							LAYOUT::LAYOUT_9.boardSize,
							LAYOUT::LAYOUT_9.sizeOfEachCell,
							LAYOUT::LAYOUT_9.distanceBetweenEachCell,
							LAYOUT::LAYOUT_9.distanceBetweenCellAndBorder, 
							LAYOUT::LAYOUT_9.alignX,
							LAYOUT::LAYOUT_9.alignY,
							LAYOUT::LAYOUT_9.sizeOfValue, 
							LAYOUT::LAYOUT_9.alignNextText,
							LAYOUT::LAYOUT_9.sizeOfNextText);
						break;
			case Game::MODE_10:
				board.init(	Game::GAME_WIDTH,
							Game::GAME_HEIGHT,
							LAYOUT::LAYOUT_10.boardSize,
							LAYOUT::LAYOUT_10.sizeOfEachCell,
							LAYOUT::LAYOUT_10.distanceBetweenEachCell,
							LAYOUT::LAYOUT_10.distanceBetweenCellAndBorder, 
							LAYOUT::LAYOUT_10.alignX,
							LAYOUT::LAYOUT_10.alignY,
							LAYOUT::LAYOUT_10.sizeOfValue, 
							LAYOUT::LAYOUT_10.alignNextText,
							LAYOUT::LAYOUT_10.sizeOfNextText);
				break;
			default:
				std::cout << "Error in UI mode\n";
			}

			player.setUserName(login.getUsername());
			player.setPassword(login.getPassword());

			startTime = std::chrono::system_clock::now(); // Start time for the game
		}

		if (login.getUsername().size() != 0 && playerList.findPlayer(login.getUsername()))
			login.setWarning(true);
		else 
			login.setWarning(false);
	}
	else if (state == Game::PLAYING) {
		/* Score */
		score = board.score;
		textScore.setString(std::to_string(score));
		textScore.setOrigin(textScore.getGlobalBounds().width / 2, textScore.getGlobalBounds().height / 2);
		player.setScore(score);

		/* Best score */
		if (score > bestScore) {
			bestScore = score;
			this->saveBestScore("Data/best_score.dat");
		}

			

		textBestScore.setString(std::to_string(bestScore));
		textBestScore.setOrigin(textBestScore.getGlobalBounds().width / 2, textBestScore.getGlobalBounds().height / 2);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && pressTime <= 0.0f) {
			pressTime = PRESS_DELAY;
			state = Game::START_MENU;

			board.clearUndoBoardStack();
			board.clearRedoBoardStack();
			board.clearUndoScoreStack();
			board.clearRedoScoreStack();
			board.clear();
			board.canMove = true;

			isWin = false;
			isGameOver = false;

			isCalculated = false;

			login.clear();
		}
		/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && pressTime <= 0.0f) {
			pressTime = PRESS_DELAY;
			state = Game::START_MENU;

			board.canMove = true;
			isCanCheckMove = true;
			isWin = false;
			isGameOver = false;

			isCalculated = false;

			login.clear();
		}*/

		if (board.isOver() || board.isWin()) {
			endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = endTime - startTime;
			float elapsedSecondsFloat = static_cast<float>(elapsed_seconds.count());
			player.setTime(elapsedSecondsFloat);

			if (board.isOver()) 
				GameOverMessage(playerList.findPlayerPosition(score, elapsedSecondsFloat));
			else 
				WinMessage(playerList.findPlayerPosition(score, elapsedSecondsFloat));

			board.canMove = false;

			if (!isCalculated) {
				
				playerList.addPlayer(player);

				std::cout << "Time taken: " << elapsed_seconds.count() << "s\n";
				isCalculated = true;
			}
		}
	}
}

/**
 * Draws the UI elements on the screen.
 * @param rt Render target to draw on
 * @param rs Current render states
 */
void UI::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	// Draw UI elements based on the current game state...
	if (state == Game::START_MENU) {
		rt.draw(backgroundStartMenu, rs);

		rt.draw(ButtonNewGame, rs);
		rt.draw(ButtonSetting, rs);
		rt.draw(ButtonTop20List, rs);
		rt.draw(ButtonResume, rs);
	}
	else if (state == Game::SETTING) {
		rt.draw(backgroundSetting, rs);
		rt.draw(textMode, rs);
		rt.draw(textOnOff, rs);
	}
	else if (state == Game::REGISTER) {
		rt.clear(sf::Color(255, 255, 255));
	}
	else if (state == Game::PLAYING) {
		rt.draw(backgroundPlaying, rs);

		rt.draw(textBestScore, rs);
		rt.draw(textScore, rs);
	}
	else
		rt.clear(sf::Color::White);
}

/**
* Sends a message to the window.
*/
void UI::sendMessage(sf::RenderWindow& window)
{
	if (isGameOver) {
		textGameOver.setOrigin(textGameOver.getGlobalBounds().width / 2, textGameOver.getGlobalBounds().height / 2);
		window.draw(textGameOver);
	}
	else if (isWin) {
		textWin.setOrigin(textWin.getGlobalBounds().width / 2, textWin.getGlobalBounds().height / 2);
		window.draw(textWin);
	}
	if (isGameOver || isWin) {
		subMessage.setOrigin(subMessage.getGlobalBounds().width / 2, subMessage.getGlobalBounds().height / 2);
		window.draw(subMessage);
	}

}

