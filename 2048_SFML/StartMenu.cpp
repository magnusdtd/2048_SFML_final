#include "StartMenu.hpp"

StartMenu::StartMenu()
{
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

	pressTime = PRESS_DELAY;
}

void StartMenu::update(float deltaTime)
{
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

}

void StartMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundStartMenu, states);

	target.draw(ButtonNewGame, states);
	target.draw(ButtonSetting, states);
	target.draw(ButtonTop20List, states);
	target.draw(ButtonResume, states);
}
