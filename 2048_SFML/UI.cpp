#include "UI.hpp"

/**
 * Constructor for the UI class.
 * Initializes the UI elements.
 */
UI::UI() : isResume(false) {
	/* Common */
	if (!font.loadFromFile("Fonts/Heavitas.ttf"))
		std::cout << "Error loading font Fonts/Heavitas.ttf\n";
	state = Game::START_MENU;
	pressTime = PRESS_DELAY;

	/* Score */	
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

	saveDataMessage.setFont(font);
	saveDataMessage.setCharacterSize(40);
	saveDataMessage.setFillColor(sf::Color(204, 0, 0));
	saveDataMessage.setPosition(550, 450);

	/*playerList.clearDataFile("Data/player_name.bin",
							"Data/player_score.bin",
							"Data/player_time.bin",
							"Data/player_password.bin");*/
	playerList.loadData("Data/player_name.bin",
						"Data/player_score.bin",
						"Data/player_time.bin",
						"Data/player_password.bin");

	for (int i = 0; i < 20; i++) {
		playerList.addPlayer("Player" + std::to_string(i), (u64)Random<int>(0, 1000), Random<double>(0, 1000), "password");
	}

	bestScore = playerList.getMaxScore();

	/*resume.clearData();*/

	resume.loadData();
}

Player UI::getPlayer() const
{
	return Player();
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

void UI::setSaveDataMessage(std::string str)
{
	saveDataMessage.setString(str);
}

void UI::handleEvent(float deltaTime, sf::Event event, sf::Vector2i position)
{
	if (state == Game::REGISTER)
		login.handleInput(event, position, state, deltaTime);
	else if (state == Game::RESUME)
		resume.handleEvent(deltaTime, event, position);
}

/**
 * Updates the UI based on the current game state.
 * @param deltaTime Time since the last frame
 * @param board Reference to the game board
 * @param tf Reference to the text field
 */
void UI::update(float deltaTime) {
	// Update UI based on the current game state...
	pressTime -= deltaTime;
	if (state == Game::START_MENU) {
		startMenu.update(deltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			switch (startMenu.SELECT_BUTTON) {
			case Game::NewGame:
				state = Game::REGISTER;
				break;
			case Game::Setting:
				state = Game::SETTING;
				break;
			case Game::Top20List:
				state = Game::TOP20LIST;
				break;
			case Game::Resume:
				state = Game::RESUME;
				isResume = true;
				break;
			}
	}
	else if (state == Game::SETTING) {
		setting.update(deltaTime);
		board.OnOffStack = setting.canUndoRedo;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			state = Game::START_MENU;
		}
	}
	else if (state == Game::TOP20LIST) {
		top20List.update(deltaTime, playerList);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			state = Game::START_MENU;
	}
	else if (state == Game::RESUME) {
		
		resume.update(deltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && 
			resume.state == Game::RESUME_PLAY &&
			pressTime <= 0.0f) {
			pressTime = PRESS_DELAY;

			state = Game::PLAYING;
			resume.state = Game::RESUME_OPTION;
			isResume = false;

			// Load the board data from the resume list
			auto temp = resume.getSelectedResumeData();
			u32 size = temp->boardStack.getSizeOfBoard();

			switch (size) {
			case Game::MODE_4:
				board.init(Game::GAME_WIDTH,
					Game::GAME_HEIGHT,
					LAYOUT::LAYOUT_4.boardSize,
					LAYOUT::LAYOUT_4.sizeOfEachCell,
					LAYOUT::LAYOUT_4.distanceBetweenEachCell,
					LAYOUT::LAYOUT_4.distanceBetweenCellAndBorder,
					LAYOUT::LAYOUT_4.alignX,
					LAYOUT::LAYOUT_4.alignY,
					LAYOUT::LAYOUT_4.sizeOfValue,
					LAYOUT::LAYOUT_4.alignNextText,
					LAYOUT::LAYOUT_4.sizeOfNextText);
				break;
			case Game::MODE_5:
				board.init(Game::GAME_WIDTH,
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
				board.init(Game::GAME_WIDTH,
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
				board.init(Game::GAME_WIDTH,
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
				board.init(Game::GAME_WIDTH,
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
				board.init(Game::GAME_WIDTH,
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
				board.init(Game::GAME_WIDTH,
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
				std::cout << "Error in RESUME MODE \n";
			}
			
			board.loadResumeData(temp);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) &&
			resume.state == Game::RESUME_OPTION &&
			resume.isNoAccountResume() &&
			pressTime <= 0.0f) {

			state = Game::START_MENU;
			resume.state = Game::RESUME_OPTION;
			isResume = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) &&
			resume.state == Game::RESUME_GO_BACK) {

			state = Game::START_MENU;
			resume.state = Game::RESUME_OPTION;
			isResume = false;
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
			switch (setting.mode) {
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

			currentPlayer.setUserName(login.getUsername());
			currentPlayer.setPassword(login.getPassword());

			startTime = std::chrono::system_clock::now(); // Start time for the game

			login.clear();
		}

		if (login.getUsername().size() != 0 && playerList.findPlayer(login.getUsername()))
			login.setWarning(true);
		else 
			login.setWarning(false);
	}
	else if (state == Game::PLAYING) {
		/* Score */
		board.update(deltaTime);

		score = board.score;
		textScore.setString(std::to_string(score));
		textScore.setOrigin(textScore.getGlobalBounds().width / 2, textScore.getGlobalBounds().height / 2);
		currentPlayer.setScore(score);

		/* Best score */
		if (score > bestScore) {
			bestScore = score;
			this->saveBestScore("Data/best_score.bin");
		}		

		textBestScore.setString(std::to_string(bestScore));
		textBestScore.setOrigin(textBestScore.getGlobalBounds().width / 2, textBestScore.getGlobalBounds().height / 2);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && 
			pressTime <= 0.0f && 
			!board.isOver() 
			&& !board.isWin()) {
			pressTime = PRESS_DELAY;
			board.canMove = false;
			setSaveDataMessage("Do you want to save your data?\nPress Y(Yes) or N(No) to continue");
			saveDataFlag = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && pressTime <= 0.f && saveDataFlag) {
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

			saveDataFlag = false;

			endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = endTime - startTime;
			float elapsedSecondsFloat = static_cast<float>(elapsed_seconds.count());
			currentPlayer.setTime(elapsedSecondsFloat);
			playerList.addPlayer(currentPlayer);

			u64** temp = board.getBoardData();
			resume.addData(currentPlayer, board.getUndoBoardStack(), board.getUndoScoreStack());
			board.clear();
			delete[] temp;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && pressTime <= 0.f && saveDataFlag) {
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

			saveDataFlag = false;
		}

		/* Game over or win */
		if (board.isOver() || board.isWin()) {
			endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = endTime - startTime;
			float elapsedSecondsFloat = static_cast<float>(elapsed_seconds.count());
			currentPlayer.setTime(elapsedSecondsFloat);

			

			if (board.isOver()) 
				GameOverMessage(position);
			else 
				WinMessage(position);

			board.canMove = false;

			if (!isCalculated) {
				position = playerList.findPlayerPosition(score, elapsedSecondsFloat);
				
				isCalculated = true;
			}

			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && pressTime <= 0.0f) {
				pressTime = PRESS_DELAY;
				state = Game::START_MENU;

				endTime = std::chrono::system_clock::now();
				elapsed_seconds = endTime - startTime;
				elapsedSecondsFloat = static_cast<float>(elapsed_seconds.count());
				currentPlayer.setTime(elapsedSecondsFloat);
				playerList.addPlayer(currentPlayer);

				board.clearUndoBoardStack();
				board.clearRedoBoardStack();
				board.clearUndoScoreStack();
				board.clearRedoScoreStack();
				board.clear();
				board.canMove = true;

				isWin = false;
				isGameOver = false;
				isCalculated = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && pressTime <= 0.0f) {
				pressTime = PRESS_DELAY;
				state = Game::INF;

				board.canMove = true;
				isCanCheckMove = true;
				isWin = false;
				isGameOver = false;

				isCalculated = false;
			}
		}
	}
	else if (state == Game::INF) {
		/* Score */
		board.update(deltaTime);

		score = board.score;
		textScore.setString(std::to_string(score));
		textScore.setOrigin(textScore.getGlobalBounds().width / 2, textScore.getGlobalBounds().height / 2);
		currentPlayer.setScore(score);

		/* Best score */
		if (score > bestScore) {
			bestScore = score;
			this->saveBestScore("Data/best_score.bin");
		}

		textBestScore.setString(std::to_string(bestScore));
		textBestScore.setOrigin(textBestScore.getGlobalBounds().width / 2, textBestScore.getGlobalBounds().height / 2);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && pressTime <= 0.0f) {
			pressTime = PRESS_DELAY;
			state = Game::START_MENU;
		}
	}
	else
		std::cout << "Invalid state in UI\n";
}

/**
 * Draws the UI elements on the screen.
 * @param rt Render target to draw on
 * @param rs Current render states
 */
void UI::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	rt.clear(sf::Color::White);
	rt.setView(rt.getDefaultView());

	// Draw UI elements based on the current game state...
	if (state == Game::START_MENU) {
		rt.draw(startMenu, rs);
	}
	else if (state == Game::SETTING) {
		rt.draw(setting, rs);
	}
	else if (state == Game::TOP20LIST) {
		rt.draw(top20List, rs);
		rt.draw(playerList, rs);
	}
	else if (state == Game::RESUME) {
		rt.draw(resume, rs);
	}
	else if (state == Game::REGISTER) {
		rt.clear(sf::Color(255, 255, 255));
		rt.draw(login, rs);
	}
	else if (state == Game::PLAYING) {
		rt.draw(board, rs);
		rt.draw(textBestScore, rs);
		rt.draw(textScore, rs);

		if (saveDataFlag)
			rt.draw(saveDataMessage, rs);
	}
	else if (state == Game::INF) {
		rt.draw(board, rs);
		rt.draw(textBestScore, rs);
		rt.draw(textScore, rs);
	}
	else
		std::cout << "Invalid state in UI\n";
}

/**
* Sends a message to the window.
*/
void UI::sendMessage(sf::RenderWindow& window)
{
	if (state == Game::PLAYING) {
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
		if (saveDataMessage.getString() != "") {
			saveDataMessage.setOrigin(saveDataMessage.getGlobalBounds().width / 2, saveDataMessage.getGlobalBounds().height / 2);
			window.draw(saveDataMessage);
		}
	}
}

/**
*@brief Saves the player data to a file.
*/
void UI::saveData()
{
	Player player = this->getPlayer();
	if (playerList.getPlayer(player.getName()) == nullptr &&
		player.getName() != "" &&
		player.getScore() != 0 &&
		player.getTime() != 0)
		playerList.addPlayer(player);

	playerList.writeMaxScore("Data/best_score.bin");

	playerList.saveData("Data/player_name.bin",
						"Data/player_score.bin",
						"Data/player_time.bin",
						"Data/player_password.bin");


	u64** temp = board.getBoardData();
	resume.addData(currentPlayer, board.getUndoBoardStack(), board.getUndoScoreStack());
	delete[] temp;

	if (!resume.isNoAccountResume())
		resume.saveData();
}