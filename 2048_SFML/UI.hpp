#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Loader.hpp"
#include "TextField.hpp"
#include "Board.hpp"
#include "layout.hpp"

namespace Game {
	enum State {
		START_MENU,
		SETTING,
		REGISTER,
		TOP20LIST,
		PLAYING
	};
	enum Mode {
		MODE_4 = 4,
		MODE_5,
		MODE_6,
		MODE_7,
		MODE_8,
		MODE_9,
		MODE_10
	};
	enum StartMenuButton {
		NewGame,
		Setting,
		Top20List,
		Resume,
		NUMBER_OF_BUTTONS
	};
	static const u32 GAME_WIDTH = 1200;
	static const u32 GAME_HEIGHT = 800;
}


class UI : public sf::Drawable {
private:
	/* Common */
	sf::Font font;
	u32 GameState;
	const float PRESS_DELAY = 0.4f;
	float pressTime;

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
	Game::Mode mode; 
	sf::Text textMode;

	/* Top 20 List && Register */
	sf::Texture backgroundTextureTop20List;
	sf::Sprite backgroundTop20List;

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
	void setState(u32 state) { this->GameState = GameState; }
	u32 getState() const { return GameState; }
	void GameOver();
	void update(float deltaTime, u64 val, TextField& tf, Board& board);
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};

#endif
