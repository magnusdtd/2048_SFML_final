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
	enum Mode {
		MODE_4,
		MODE_5,
		MODE_6,
		MODE_7,
		MODE_8,
		MODE_9,
		MODE_10
	};
	namespace LAYOUT_4 {
		static u32 BOARD_SIZE = 4;
		static float sizeOfEachCell = 170.f;
		static float distanceBetweenEachCell = 5.f;
		static float distanceBetweenCellAndBorder = 20.f;
	}
	namespace LAYOUT_5 {
		static u32 BOARD_SIZE = 5;
		static float sizeOfEachCell = 125.f;
		static float distanceBetweenEachCell = 5.f;
		static float distanceBetweenCellAndBorder = 20.f;
	}
	namespace LAYOUT_6 {
		static u32 BOARD_SIZE = 6;
		static float sizeOfEachCell = 100.f;
		static float distanceBetweenEachCell = 5.f;
		static float distanceBetweenCellAndBorder = 20.f;
	}
	namespace LAYOUT_7 {
		static u32 BOARD_SIZE = 7;
		static float sizeOfEachCell = 90.f;
		static float distanceBetweenEachCell = 5.f;
		static float distanceBetweenCellAndBorder = 20.f;
	}
	namespace LAYOUT_8 {
		static u32 BOARD_SIZE = 8;
		static float sizeOfEachCell = 75.f;
		static float distanceBetweenEachCell = 5.f;
		static float distanceBetweenCellAndBorder = 20.f;
	}
	namespace LAYOUT_9 {
		static u32 BOARD_SIZE = 9;
		static float sizeOfEachCell = 70.f;
		static float distanceBetweenEachCell = 5.f;
		static float distanceBetweenCellAndBorder = 20.f;
	}
	namespace LAYOUT_10 {
		static u32 BOARD_SIZE = 10;
		static float sizeOfEachCell = 130.f;
		static float distanceBetweenEachCell = 5.f;
		static float distanceBetweenCellAndBorder = 20.f;
	}
	static State state = PLAYING;
	void StartGame(sf::RenderWindow& window);
	void Register(sf::RenderWindow& window, TextField& tf);
	void PlayGame(sf::RenderWindow& window, float deltaTime, Board& board, UI& ui);
}
#endif