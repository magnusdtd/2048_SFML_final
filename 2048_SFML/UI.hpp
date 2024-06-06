#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Loader.hpp"
#include "TextField.hpp"
#include "Board.hpp"
#include "layout.hpp"


class UI : public sf::Drawable {
private:
	/* Common */
	sf::Font font;
	const float PRESS_DELAY = 0.4f;
	float pressTime;
	Game::State state = Game::START_MENU;

	/* Start Menu */
	sf::Texture backgroundTextureStartMenu;
	sf::Sprite backgroundStartMenu;
	u32 SELECT_BUTTON;
	sf::Text ButtonNewGame;
	sf::Text ButtonSetting;
	sf::Text ButtonTop20List;
	sf::Text ButtonResume;
	
	/* Setting */
	sf::Texture backgroundTextureSetting;
	sf::Sprite backgroundSetting;
	u32 whichButton;

	Game::Mode mode; // 4x4, 5x5, 6x6, 7x7, 8x8, 9x9, 10x10
	u32 buttonMode;
	sf::Text textMode;

	u32 buttonOnOff;
	sf::Text textOnOff;


	/* Top 20 List && Register */
	sf::Texture backgroundTextureTop20List;
	sf::Sprite backgroundTop20List;
	TextField tf;

	/* Playing */
	sf::Texture backgroundTexturePlaying;
	sf::Sprite backgroundPlaying;
	sf::Text textBestScore;
	sf::Text textScore;
	sf::Text textGameOver;
	sf::Text textResume;
	u64 bestScore = 0;
	u64 score = 0;
	bool newScore = false;
	bool gameOver = false;
	
public:
	UI();
	Game::State getState() const;
	void GameOver();
	void update(float deltaTime, Board& board);
	void handleInput(sf::Event event, sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};

#endif
