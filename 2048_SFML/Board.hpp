#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cell.hpp"

class Board : public sf::Drawable {
private:
	Cell **cells;
	sf::Font font;

	u64 score;

	const float PRESS_DELAY = 0.5f;
	float pressTime;

	sf::Texture borderTexture;
	sf::Sprite border;
	float sizeOfEachCell = 60.f;
	float distanceBetweenEachCell = 5.f;
	float distanceBetweenCellAndBorder = 20.f;

	u32 size = 10;	// Default size of board
public:
	Board(u32 width, u32 height);
	void init(u32 width, u32 height);
	~Board();
	/*bool isGameOver();
	void MoveCheck();
	bool CellCheck(u64 i, u64 j);
	void MakeMovement();
	void NewPieces();*/

	u64 getScore() const;

	void UpMove();
	void DownMove();
	void LeftMove();
	void RightMove();
	void update(float deltaTime);

	virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};

#endif
