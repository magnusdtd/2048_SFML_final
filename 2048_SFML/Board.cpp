#include "Board.hpp"

Board::Board() {
	pressTime = 0.0f;
	score = 0;
	size = 0;

	if (!font.loadFromFile("resources/font.ttf"))
		std::cout << "Error loading font\n";
	
	this->cells = nullptr;
	sizeOfEachCell = 0.f;
	distanceBetweenEachCell = 0.f;
	distanceBetweenCellAndBorder = 0.f;
	distanceBetweenCellAndScore = 0.f;
	sizeofValue = 0;
}

void Board::init(	u32 width,
					u32 height,
					u32 size,
					float sizeOfEachCell,
					float distanceBetweenEachCell,
					float distanceBetweenCellAndBorder,
					float distanceBetweenCellAndScore,
					u32 sizeofValue)
{
	this->size = size;
	this->sizeOfEachCell = sizeOfEachCell;
	this->distanceBetweenEachCell = distanceBetweenEachCell;
	this->distanceBetweenCellAndBorder = distanceBetweenCellAndBorder;
	this->distanceBetweenCellAndScore = distanceBetweenCellAndScore;
	this->sizeofValue = sizeofValue;

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


	this->cells = new Cell * [this->size];
	for (u32 i = 0; i < this->size; i++)
		this->cells[i] = new Cell[this->size];

	for (u32 i = 0; i < this->size; i++)
		for (u32 j = 0; j < this->size; j++)
			this->cells[i][j].init(	x0 + i * this->sizeOfEachCell + i * this->distanceBetweenEachCell,
									y0 + j * this->sizeOfEachCell + j * this->distanceBetweenEachCell,
									font,
									this->sizeOfEachCell,
									distanceBetweenCellAndScore, 
									sizeofValue);


	/* Random intialize two Cell of board */
	u32 init1 = Random<u32>(0, size - 1), init2 = Random<u32>(0, size - 1), init3 = 0, init4 = 0;
	while (true) {
		init3 = Random<u32>(0, size - 1);
		init4 = Random<u32>(0, size - 1);
		if (init3 != init1 && init4 != init2)
			break;
	}
	u64 temp = static_cast<u64>(Random<u32>(1, 2)) * 2;
	this->cells[init1][init2].setValue(temp);
	this->cells[init3][init4].setValue(temp);


	/* Push first state in undo stack */
	u64* tempState = new u64[size * size];
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			tempState[i * size + j] = this->cells[i][j].getValue();
	undoStack.push(tempState, size * size);
	delete[] tempState;
}

Board::~Board() {
	for (u32 i = 0; i < size; i++) {
		delete[] this->cells[i];
		this->cells[i] = nullptr;
	}
	delete[] this->cells;
	this->cells = nullptr;

	std::cout << "Succesful free memory in Board class !!!\n";
}

bool Board::isEqual()
{
	std::cout << "CKECK MOVE 1\n";
	u64* temp = undoStack.top();
	if (temp == nullptr) {
		std::cout << "CKECK MOVE 2\n";
		return false;
	}
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			if (temp[i * size + j] != this->cells[i][j].getValue()) {
				std::cout << "CKECK MOVE 3\n";
				return false;
			}
	std::cout << "CKECK MOVE 4\n";
	return true;
}

bool Board::isOver() {
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			if (this->cells[i][j].getValue() == 0)
				return false;
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++) {
			if (i < size - 1 && this->cells[i][j] == this->cells[i + 1][j])
				return false;
			if (j < size - 1 && this->cells[i][j] == this->cells[i][j + 1])
				return false;
		}
	return true;
}

bool Board::isWin()
{
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			if (this->cells[i][j].getValue() == 2048)
				return true;
	return false;
}

void Board::checkMove()
{
	if (!this->isEqual()) {
		this->newCell();
		u64* temp = new u64[size * size];
		for (u32 i = 0; i < size; i++)
			for (u32 j = 0; j < size; j++)
				temp[i * size + j] = this->cells[i][j].getValue();
		undoStack.push(temp, size * size);
		delete[] temp;
		temp = nullptr;
	}
	if (isWin()) {
		std::cout << "You Win\n";
	}
	else if (isOver()) {
		std::cout << "Game Over\n";
	}
	else {
		std::cout << "Game Continue\n";
	}
}

void Board::newCell() {
	int x, y;
	while (true)
	{
		x = rand() % size;
		y = rand() % size;
		if (this->cells[x][y].getValue() == 0) {
			this->cells[x][y].setValue(2);
			break;
		}
	}
}

u64 Board::getScore() const {
	return score;
}

void Board::UpMove() {
	int x, y;
	for (int i = 0; i < (s32)size; i++) {
		x = i, y = 0;
		for (int j = 1; j < (s32)size; j++) {
			if (this->cells[i][j].getValue() != 0) {
				if (this->cells[i][j - 1].getValue() == 0 || this->cells[i][j - 1] == this->cells[i][j]) {
					if (this->cells[x][y] == this->cells[i][j]) {
						// update score
						this->cells[x][y] *= 2;
						this->cells[i][j].setValue(0);
						score += this->cells[x][y].getValue();
					}
					else {
						if (this->cells[x][y].getValue() == 0) {
							this->cells[x][y] = this->cells[i][j];
							this->cells[i][j].setValue(0);
						}
						else {
							this->cells[x][++y] = this->cells[i][j];
							this->cells[i][j].setValue(0);
						}
					}
				}
				else y++;
			}
		}
	}
}

void Board::DownMove() {
	int x, y;
	for (int i = 0; i < (s32)size; i++) {
		x = i, y = (s32)size - 1;
		for (int j = (s32)size - 2; j >= 0; j--) {
			if (this->cells[i][j].getValue() != 0) {
				if (this->cells[i][j + 1].getValue() == 0 || this->cells[i][j + 1] == this->cells[i][j]) {
					if (this->cells[x][y] == this->cells[i][j]) {
						// update score
						this->cells[x][y] *= 2;
						this->cells[i][j].setValue(0);
						score += this->cells[x][y].getValue();
					}
					else {
						if (this->cells[x][y].getValue() == 0) {
							this->cells[x][y] = this->cells[i][j];
							this->cells[i][j].setValue(0);
						}
						else {
							this->cells[x][--y] = this->cells[i][j];
							this->cells[i][j].setValue(0);
						}
					}
				}
				else y--;
			}
		}
	}
}

void Board::LeftMove() {
	int x, y;	
	for (int j = 0; j < (s32)size; j++) {
		x = 0, y = j;
		for (int i = 1; i < (s32)size; i++) {
			if (this->cells[i][j].getValue() != 0) {
				if (this->cells[i - 1][j].getValue() == 0
					|| this->cells[i - 1][j] == this->cells[i][j]) {
					if (this->cells[x][y].getValue() == this->cells[i][j].getValue()) {
						// update score
						this->cells[x][y] *= 2;
						this->cells[i][j].setValue(0);
						score += this->cells[x][y].getValue();
					}
					else {
						if (this->cells[x][y].getValue() == 0) {
							this->cells[x][y] = this->cells[i][j];
							this->cells[i][j].setValue(0);
						}
						else {
							this->cells[++x][y] = this->cells[i][j];
							this->cells[i][j].setValue(0);
						}
					}
				}
				else x++;
			}
		}
	}
}

void Board::RightMove() {
	int x, y;
	for (int j = 0; j < (s32)size; j++) {
		x = (s32)size - 1, y = j;
		for (int i = (s32)size - 2; i >= 0; i--) {
			if (this->cells[i][j].getValue() != 0) {
				if (this->cells[i + 1][j].getValue() == 0
					|| this->cells[i + 1][j] == this->cells[i][j]) {
					if (this->cells[x][y].getValue() == this->cells[i][j].getValue()) {
						// update score
						this->cells[x][y] *= 2;
						this->cells[i][j].setValue(0);
						score += this->cells[x][y].getValue();
					}
					else {
						if (this->cells[x][y].getValue() == 0) {
							this->cells[x][y] = this->cells[i][j];
							this->cells[i][j].setValue(0);
						}
						else {
							this->cells[--x][y] = this->cells[i][j];
							this->cells[i][j].setValue(0);
						}
					}
				}
				else x--;
			}
		}
	}
}

void Board::Undo()
{
	if (undoStack.empty())
		return;
	u64* temp = undoStack.top();
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			this->cells[i][j].setValue(temp[i * size + j]);
	redoStack.push(temp, size * size);
	delete[] temp;
}

void Board::Redo()
{
	if(redoStack.empty())
		return;
	u64* temp = redoStack.top();
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			this->cells[i][j].setValue(temp[i * size + j]);
	undoStack.push(temp, size * size);
	delete[] temp;
}

void Board::update(float deltaTime) {
	pressTime -= deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.0f) {
		pressTime = PRESS_DELAY;
		this->UpMove();
		this->checkMove();
		std::cout << "Up Check\n";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.0f) {
		pressTime = PRESS_DELAY;
		this->DownMove();
		this->checkMove();
		std::cout << "Down Check\n";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pressTime <= 0.0f) {
		pressTime = PRESS_DELAY;
		this->LeftMove();
		this->checkMove();
		std::cout << "Left Check\n";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pressTime <= 0.0f) {
		pressTime = PRESS_DELAY;
		this->RightMove();
		this->checkMove();
		std::cout << "Right Check\n";
	}
}

void Board::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	rt.draw(border, rs); // Draw table

	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			rt.draw(this->cells[i][j], rs); // Draw this->cells
}
