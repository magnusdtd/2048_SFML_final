#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Cell.hpp"

constexpr float PRESS_DELAY = 0.5f;

class Board : public sf::Drawable {
private:
	u32 size = 5;
	Cell **cells;
	sf::Font font;

	u64 score = 0;

	float pressTime;

	sf::VertexArray border;
	float size_of_each_cell = 70.f;
	float distance_of_each_cell = 20.f;
	float distance_between_cell_and_border = 10.f;
public:
	Board();
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
