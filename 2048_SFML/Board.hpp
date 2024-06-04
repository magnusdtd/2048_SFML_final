#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cell.hpp"
#include "utils.hpp"

class Board : public sf::Drawable {
private:
	Cell **cells;
	sf::Font font;

	u64 score;

	const float PRESS_DELAY = 0.3f;
	float pressTime;

	sf::Texture borderTexture;
	sf::Sprite border;
	float sizeOfEachCell;
	float distanceBetweenEachCell;
	float distanceBetweenCellAndBorder;

	u32 size;

	Stack undoStack;
	Stack redoStack;
	Stack scoreStack;
public:
	Board();
	~Board();
	void init(	u32 width,
				u32 height,
				u32 size,
				float sizeOfEachCell,
				float distanceBetweenEachCell,
				float distanceBetweenCellAndBorder);

	bool isEqual();
	bool isOver();
	bool isWin();
	void checkMove();
	void newCell();
	u64 getScore() const;

	void UpMove();
	void DownMove();
	void LeftMove();
	void RightMove();
	void Undo();
	void Redo();

	void update(float deltaTime);

	virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};

#endif