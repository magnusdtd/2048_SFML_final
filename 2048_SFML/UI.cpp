#include "UI.hpp"

UI::UI() {
	/* Common */
	if (!font.loadFromFile("resources/font.ttf"))
		std::cout << "Error loading font\n";
	GameState = Game::START_MENU;
	pressTime = 0.f;

	/* Start Menu */
	backgroundTextureStartMenu.loadFromFile("resources/StartMenu.png");
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
	backgroundTextureSetting.loadFromFile("resources/Setting.png");
	backgroundSetting.setTexture(backgroundTextureSetting);
	mode = Game::Mode::MODE_4; // Default mode

	/* Top 20 list && Register */
	backgroundTextureTop20List.loadFromFile("resources/Top20List.png");
	backgroundTop20List.setTexture(backgroundTextureTop20List);

	/* Playing */
	backgroundTexturePlaying.loadFromFile("resources/background.png");
	backgroundPlaying.setTexture(backgroundTexturePlaying);
	
	bestScore = Input::loadBestScore();
	textBestScore.setFont(font);
	textBestScore.setString(std::to_string(bestScore));
	textBestScore.setCharacterSize(32);
	textBestScore.setFillColor(sf::Color(0, 0, 0));
	textBestScore.setPosition(1010.f, 365.f);

	textScore.setFont(font);
	textScore.setString(std::to_string(score));
	textScore.setCharacterSize(32);
	textScore.setFillColor(sf::Color(0, 0, 0));
	textScore.setPosition(1010.f, 582.f);

	textGameOver.setFont(font);
	textGameOver.setString("Game Over");
	textGameOver.setCharacterSize(35);
	textGameOver.setFillColor(sf::Color(0, 0, 0));
	textGameOver.setPosition(200, 300);

	textResume.setFont(font);
	textResume.setString("Resume");
	textResume.setCharacterSize(35);
	textResume.setFillColor(sf::Color(0, 0, 0));
	textResume.setPosition(200, 300);
}

void UI::GameOver() {
	if (score > bestScore) {
		newScore = true;
		Input::saveBestScore(score);
	}
	else
		gameOver = true;
}

void UI::update(float deltaTime, u64 val, TextField &tf, Board &board) {
	pressTime -= deltaTime;
	if (GameState == Game::State::START_MENU) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.f) {
			(SELECT_BUTTON += (Game::NUMBER_OF_BUTTONS - 1)) %= Game::NUMBER_OF_BUTTONS;
			pressTime = PRESS_DELAY;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.f) {
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
			if (SELECT_BUTTON == Game::StartMenuButton::NewGame)
				GameState = Game::State::REGISTER;
			else if (SELECT_BUTTON == Game::StartMenuButton::Setting)
				GameState = Game::State::SETTING;
			else if (SELECT_BUTTON == Game::StartMenuButton::Top20List)
				GameState = Game::State::TOP20LIST;
			else if (SELECT_BUTTON == Game::StartMenuButton::Resume)
				GameState = Game::State::PLAYING;

	}
	else if (GameState == Game::State::SETTING) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			GameState = Game::State::START_MENU;
	}
	else if (GameState == Game::State::TOP20LIST) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			GameState = Game::State::START_MENU;
	}
	else if (GameState == Game::State::REGISTER) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && tf.getText().size() != 0) {
			GameState = Game::State::PLAYING;
			switch (mode) {
			case Game::MODE_4:
				board.init(Game::GAME_WIDTH,
					Game::GAME_HEIGHT,
					LAYOUT::LAYOUT_4::BOARD_SIZE,
					LAYOUT::LAYOUT_4::sizeOfEachCell,
					LAYOUT::LAYOUT_4::distanceBetweenEachCell,
					LAYOUT::LAYOUT_4::distanceBetweenCellAndBorder);
				break;
			case Game::MODE_5:
				board.init(Game::GAME_WIDTH,
					Game::GAME_HEIGHT,
					LAYOUT::LAYOUT_5::BOARD_SIZE,
					LAYOUT::LAYOUT_5::sizeOfEachCell,
					LAYOUT::LAYOUT_5::distanceBetweenEachCell,
					LAYOUT::LAYOUT_5::distanceBetweenCellAndBorder);
				break;
			case Game::MODE_6:
				board.init(Game::GAME_WIDTH,
					Game::GAME_HEIGHT,
					LAYOUT::LAYOUT_6::BOARD_SIZE,
					LAYOUT::LAYOUT_6::sizeOfEachCell,
					LAYOUT::LAYOUT_6::distanceBetweenEachCell,
					LAYOUT::LAYOUT_6::distanceBetweenCellAndBorder);
				break;
			case Game::MODE_7:
				board.init(Game::GAME_WIDTH,
					Game::GAME_HEIGHT,
					LAYOUT::LAYOUT_7::BOARD_SIZE,
					LAYOUT::LAYOUT_7::sizeOfEachCell,
					LAYOUT::LAYOUT_7::distanceBetweenEachCell,
					LAYOUT::LAYOUT_7::distanceBetweenCellAndBorder);
				break;
			case Game::MODE_8:
				board.init(Game::GAME_WIDTH,
					Game::GAME_HEIGHT,
					LAYOUT::LAYOUT_8::BOARD_SIZE,
					LAYOUT::LAYOUT_8::sizeOfEachCell,
					LAYOUT::LAYOUT_8::distanceBetweenEachCell,
					LAYOUT::LAYOUT_8::distanceBetweenCellAndBorder);
				break;
			case Game::MODE_9:
				board.init(Game::GAME_WIDTH,
					Game::GAME_HEIGHT,
					LAYOUT::LAYOUT_9::BOARD_SIZE,
					LAYOUT::LAYOUT_9::sizeOfEachCell,
					LAYOUT::LAYOUT_9::distanceBetweenEachCell,
					LAYOUT::LAYOUT_9::distanceBetweenCellAndBorder);
				break;
			case Game::MODE_10:
				board.init(Game::GAME_WIDTH,
					Game::GAME_HEIGHT,
					LAYOUT::LAYOUT_10::BOARD_SIZE,
					LAYOUT::LAYOUT_10::sizeOfEachCell,
					LAYOUT::LAYOUT_10::distanceBetweenEachCell,
					LAYOUT::LAYOUT_10::distanceBetweenCellAndBorder);
				break;
			default:
				std::cout << "Error in UI mode\n";
			}
		}
	}
	else if (GameState == Game::State::PLAYING) {
		score = val;
		textScore.setString(std::to_string(score));
		textScore.setOrigin(textScore.getGlobalBounds().width / 2, textScore.getGlobalBounds().height / 2);

		if (score > bestScore) {
			textBestScore.setString(std::to_string(score));
			textBestScore.setOrigin(textBestScore.getGlobalBounds().width / 2, textBestScore.getGlobalBounds().height / 2);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			GameState = Game::State::START_MENU;
	}

}

void UI::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	if (GameState == Game::START_MENU) {
		rt.draw(backgroundStartMenu, rs);

		rt.draw(ButtonNewGame, rs);
		rt.draw(ButtonSetting, rs);
		rt.draw(ButtonTop20List, rs);
		rt.draw(ButtonResume, rs);

	}
	else if (GameState == Game::SETTING)
		rt.draw(backgroundSetting, rs);
	else if (GameState == Game::TOP20LIST)
		rt.draw(backgroundTop20List, rs);
	else if (GameState == Game::REGISTER)
		rt.draw(backgroundTop20List, rs);
	else if (GameState == Game::PLAYING) {
		rt.draw(backgroundPlaying, rs);

		rt.draw(textBestScore, rs);
		rt.draw(textScore, rs);
		rt.draw(textBestScore, rs);
		rt.draw(textScore, rs);


		if (gameOver)
			rt.draw(textGameOver, rs);
		if (newScore)
			rt.draw(textResume, rs);
	}
}

