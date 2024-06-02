#include "Board.hpp"

Board::Board() {
	pressTime = 0.0f;
	score = 0;
	size = 0;

	if (!font.loadFromFile("resources/font.ttf"))
		std::cout << "Error loading font\n";
	
	cells = nullptr;
	sizeOfEachCell = 0.f;
	distanceBetweenEachCell = 0.f;
	distanceBetweenCellAndBorder = 0.f;
}

void Board::init(	u32 width, 
					u32 height, 
					u32 size, 
					float sizeOfEachCell, 
					float distanceBetweenEachCell, 
					float distanceBetweenCellAndBorder) 
{
	this->size = size;
	this->sizeOfEachCell = sizeOfEachCell;
	this->distanceBetweenEachCell = distanceBetweenEachCell;
	this->distanceBetweenCellAndBorder = distanceBetweenCellAndBorder;

	// Fomula
	float w = this->size * this->sizeOfEachCell + this->distanceBetweenEachCell * (this->size - 1) + this->distanceBetweenCellAndBorder * 2;
	float h = this->size * this->sizeOfEachCell + this->distanceBetweenEachCell * (this->size - 1) + this->distanceBetweenCellAndBorder * 2;
	float x0 = height / 2.f, y0 = height / 2.f;
	x0 -= this->size / 2.f * this->sizeOfEachCell + 0.5f * (this->size - 1) * this->distanceBetweenEachCell;
	y0 -= this->size / 2.f * this->sizeOfEachCell + 0.5f * (this->size - 1) * this->distanceBetweenEachCell;

	/* Border */
	borderTexture.loadFromFile("resources/border.png");
	border.setTexture(borderTexture);
	border.setPosition(x0 - this->distanceBetweenCellAndBorder, y0 - this->distanceBetweenCellAndBorder);
	border.scale(w / borderTexture.getSize().x, h / borderTexture.getSize().y);


	cells = new Cell * [this->size];
	for (u32 i = 0; i < this->size; i++)
		cells[i] = new Cell[this->size];

	for (u32 i = 0; i < this->size; i++)
		for (u32 j = 0; j < this->size; j++)
			cells[i][j].init(	x0 + i * this->sizeOfEachCell + i * this->distanceBetweenEachCell,
								y0 + j * this->sizeOfEachCell + j * this->distanceBetweenEachCell,
								font,
								this->sizeOfEachCell);


	/* Random intialize two Cell of board */
	srand((unsigned int)time(nullptr));
	size_t init1 = rand() % this->size, init2 = rand() % this->size, init3 = 0, init4 = 0;
	while (true) {
		init3 = rand() % this->size;
		init4 = rand() % this->size;
		if (init3 != init1 && init4 != init2)
			break;
	}
	u64 temp = (static_cast<u64>(rand() % 2) + 1) * 2;
	cells[init1][init2].setValue(temp);
	cells[init3][init4].setValue(temp);
}

Board::~Board() {
	for (u32 i = 0; i < size; i++) {
		delete[] cells[i];
		cells[i] = nullptr;
	}
	delete[] cells;
	cells = nullptr;

	std::cout << "Succesful free memory in Board class !!!\n";
}


u64 Board::getScore() const {
	return score;
}



void Board::UpMove() {
	int x, y;
	for (int j = 0; j < (s32)size; j++) {
		x = 0; y = j;
		for (int i = 1; i < (s32)size; i++) {
			if (cells[i][j].getValue() != 0) {
				if (cells[i - 1][j].getValue() == 0 
					|| cells[i - 1][j] == cells[i][j]) {
					if (cells[x][y] == cells[i][j]) {
						// update score
						cells[x][y] *= 2;
						cells[i][j].setValue(0);
						score += cells[x][y].getValue();
					}
					else if (cells[x][y].getValue() == 0) {
						cells[x][y] = cells[i][j];
						cells[i][j].setValue(0);
					}
					else {
						cells[++x][y] = cells[i][j];
						cells[i][j].setValue(0);
					}
				}
				else x++;
			}
		}
	}
}

void Board::DownMove() {
	int x, y;
	for (int j = 0; j < (s32)size; j++) {
		x = (s32)size - 1, y = j;
		for (int i = (s32)size - 2; i >= 0; i--) {
			if (cells[i][j].getValue() != 0) {
				if (cells[i + 1][j].getValue() == 0 
					|| cells[i + 1][j] == cells[i][j]) {
					if (cells[x][y].getValue() == cells[i][j].getValue()) {
						// update score
						cells[x][y] *= 2;
						cells[i][j].setValue(0);
						score += cells[x][y].getValue();
					}
					else {
						if (cells[x][y].getValue() == 0) {
							cells[x][y] = cells[i][j];
							cells[i][j].setValue(0);
						}
						else {
							cells[--x][y] = cells[i][j];
							cells[i][j].setValue(0);
						}
					}
				}
				else x--;
			}
		}
	}
}

void Board::LeftMove() {
	int x, y;
	for (int i = 0; i < (s32)size; i++) {
		x = i, y = 0;
		for (int j = 1; j < (s32)size; j++) {
			if (cells[i][j].getValue() != 0) {
				if (cells[i][j - 1].getValue() == 0 || cells[i][j - 1] == cells[i][j]) {
					if (cells[x][y] == cells[i][j]) {
						// update score
						cells[x][y] *= 2;
						cells[i][j].setValue(0);
						score += cells[x][y].getValue();
					}
					else {
						if (cells[x][y].getValue() == 0) {
							cells[x][y] = cells[i][j];
							cells[i][j].setValue(0);
						}
						else {
							cells[x][++y] = cells[i][j];
							cells[i][j].setValue(0);
						}
					}
				}
				else y++;
			}
		}
	}
}

void Board::RightMove() {
	int x, y;
	for (int i = 0; i < (s32)size; i++) {
		x = i, y = (s32)size - 1;
		for (int j = (s32)size - 2; j >= 0; j--) {
			if (cells[i][j].getValue() != 0) {
				if (cells[i][j + 1].getValue() == 0 || cells[i][j + 1] == cells[i][j]) {
					if (cells[x][y] == cells[i][j]) {
						// update score
						cells[x][y] *= 2;
						cells[i][j].setValue(0);
						score += cells[x][y].getValue();
					}
					else {
						if (cells[x][y].getValue() == 0) {
							cells[x][y] = cells[i][j];
							cells[i][j].setValue(0);
						}
						else {
							cells[x][--y] = cells[i][j];
							cells[i][j].setValue(0);
						}
					}
				}
				else y--;
			}
		}
	}
}

void Board::update(float deltaTime) {
	pressTime -= deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.0f) {
		pressTime = PRESS_DELAY;
		UpMove();
		std::cout << "Up Check\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.0f) {
		pressTime = PRESS_DELAY;
		DownMove();
		std::cout << "Down Check\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pressTime <= 0.0f) {
		pressTime = PRESS_DELAY;
		LeftMove();
		std::cout << "Left Check\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pressTime <= 0.0f) {
		pressTime = PRESS_DELAY;
		RightMove();
		std::cout << "Right Check\n";
	}
}

void Board::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	rt.draw(border, rs); // Draw table

	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			rt.draw(cells[i][j], rs); // Draw cells
}
