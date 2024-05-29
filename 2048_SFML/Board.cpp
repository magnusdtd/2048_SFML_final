#include "Board.hpp"

Board::Board(): border(sf::LinesStrip, 5) {
	pressTime = 0.0f;

	if (!font.loadFromFile("resources/font.ttf"))
		std::cout << "Error loading font\n";

	// Fomula
	float w = size * size_of_each_cell + distance_of_each_cell * (size - 1) + distance_between_cell_and_border;
	float h = size * size_of_each_cell + distance_of_each_cell * (size - 1) + distance_between_cell_and_border;
	float x0 = Game::GAME_HEIGHT / 2.f, y0 = Game::GAME_HEIGHT / 2.f;
	x0 -= size / 2.f * size_of_each_cell + 0.5f * (size - 1) * distance_of_each_cell;
	y0 -= size / 2.f * size_of_each_cell + 0.5f * (size - 1) * distance_of_each_cell;

	/* Border */
	border[0].position = sf::Vector2f(x0 - distance_between_cell_and_border, y0 - distance_between_cell_and_border);
	border[1].position = sf::Vector2f(x0 + w, y0 - distance_between_cell_and_border);
	border[2].position = sf::Vector2f(x0 + w, y0 + h);
	border[3].position = sf::Vector2f(x0 - distance_between_cell_and_border, y0 + h);
	border[4].position = border[0].position;

	for (u32 i = 0; i < border.getVertexCount(); i++) {
		border[i].color = sf::Color::Red;
	}


	cells = new Cell * [size];
	for (u32 i = 0; i < size; i++)
		cells[i] = new Cell[size];

	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			cells[i][j].init(	x0 + i * size_of_each_cell + i * distance_of_each_cell,
								y0 + j * size_of_each_cell + j * distance_of_each_cell, 
								font, 
								size_of_each_cell);


	/* Random intialize two Cell of board */
	srand((unsigned int)time(nullptr));
	size_t init1 = rand() % size, init2 = rand() % size, init3 = 0, init4 = 0;
	while (true) {
		init3 = rand() % size;
		init4 = rand() % size;
		if (init3 != init1 && init4 != init2) 
			break;
	}
	u64 temp = (static_cast<u64>(rand() % 2) + 1) * 2;
	cells[init1][init2].setValue(temp);
	cells[init3][init4].setValue(temp);
}

Board::~Board() {
	for (u32 i = 0; i < size; i++)
		delete[] cells[i];
	delete[] cells;

	std::cout << "Free memory\n";
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
