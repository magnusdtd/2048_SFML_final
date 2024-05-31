#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/graphics.hpp>
#include "utils.hpp"
#include "TextField.hpp"
#include "Board.hpp"
#include "UI.hpp"

namespace Game {
	static u32 GAME_WIDTH = 1200;
	static u32 GAME_HEIGHT = 800;
	enum State {
		START_MENU,
		REGISTER,
		PLAYING
	};
	static State state = PLAYING;
	void StartGame(sf::RenderWindow& window);
	void Register(sf::RenderWindow& window, TextField& tf);
	void PlayGame(sf::RenderWindow& window, float deltaTime, Board& board, UI& ui);
}
#endif