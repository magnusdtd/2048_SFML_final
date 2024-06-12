#include "Board.hpp"

/**
 * @brief Default constructor for Board.
 */
Board::Board() {
	pressTime = 0.0f;
	score = 0;
	size = 0;
	OnOffStack = false;
	isUndo = false;
	isRedo = false;
	canMove = true;

	if (!font.loadFromFile("Fonts/Heavitas.ttf"))
		std::cout << "Error loading font from Fonts/Heavitas.ttf\n";

	if (!backgroundTexturePlaying.loadFromFile("Texture/background.png"))
		std::cout << "Error loading texture from Texture/background.png\n";
	backgroundPlaying.setTexture(backgroundTexturePlaying);

	if (!borderTexture.loadFromFile("Texture/border.png"))
		std::cout << "Error loading texture from Texture/border.png\n";
	border.setTexture(borderTexture);
	
	this->cells = nullptr;
}

/**
 * @brief Initializes the board.
 */
void Board::init(u32 width,
				u32 height,
				u32 size,
				float sizeOfEachCell,
				float distanceBetweenEachCell,
				float distanceBetweenCellAndBorder,
				float alignX,
				float alignY,
				u32 sizeofValue, 
				float alignNewText,
				u32 sizeOfNewText)
{
	this->size = size;
	pressTime = 0.0f;
	score = 0;
	isUndo = false;
	isRedo = false;

	/* Fomula */
	float w = this->size * sizeOfEachCell + distanceBetweenEachCell * (this->size - 1) + distanceBetweenCellAndBorder * 2;
	float h = this->size * sizeOfEachCell + distanceBetweenEachCell * (this->size - 1) + distanceBetweenCellAndBorder * 2;
	float x0 = height / 2.f, y0 = height / 2.f;
	x0 -= this->size / 2.f * sizeOfEachCell + 0.5f * (this->size - 1) * distanceBetweenEachCell;
	y0 -= this->size / 2.f * sizeOfEachCell + 0.5f * (this->size - 1) * distanceBetweenEachCell;

	/* Border */
	border.setPosition(x0 - distanceBetweenCellAndBorder, y0 - distanceBetweenCellAndBorder);
	border.setScale(w / borderTexture.getSize().x, h / borderTexture.getSize().y);

	this->cells = new Cell * [this->size];
	for (u32 i = 0; i < this->size; i++)
		this->cells[i] = new Cell[this->size];

	for (u32 i = 0; i < this->size; i++)
		for (u32 j = 0; j < this->size; j++)
			this->cells[i][j].init(	x0 + i * sizeOfEachCell + i * distanceBetweenEachCell,
									y0 + j * sizeOfEachCell + j * distanceBetweenEachCell,
									font,
									sizeOfEachCell,
									alignX, 
									alignY, 
									sizeofValue, 
									alignNewText,
									sizeOfNewText);

	this->clearNewCells();

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
	this->cells[init1][init2].isNew = true;

	this->cells[init3][init4].setValue(temp);
	this->cells[init3][init4].isNew = true;



	/* Push first state in undo stack */
	u64* tempState = new u64[size * size];
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			tempState[i * size + j] = this->cells[i][j].getValue();
	undoBoardStack.push(tempState, size * size);
	delete[] tempState;

	undoScoreStack.push(score);
}

/**
 * @brief Destructor for Board.
 */
Board::~Board() {
	for (u32 i = 0; i < size; i++) {
		delete[] this->cells[i];
		this->cells[i] = nullptr;
	}
	delete[] this->cells;
	this->cells = nullptr;

	std::cout << "Succesful free memory in Board class !!!\n";
}

/**
 * @brief Checks if the board state is equal to the previous state.
 * @return True if the board state is equal to the previous state, false otherwise.
 */
bool Board::isEqual()
{
	u64* temp = undoBoardStack.top();
	if (temp == nullptr) {
		return false;
	}
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			if (temp[i * size + j] != this->cells[i][j].getValue()) {
				return false;
			}
	return true;
}

/**
 * @brief Checks if the game is over.
 * @return True if the game is over, false otherwise.
 */
bool Board::isOver() {
	if (size == 0)
		return false;

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

/**
 * @brief Checks if the player has won the game.
 * @return True if the player has won, false otherwise.
 */
bool Board::isWin()
{
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			if (this->cells[i][j].getValue() == 2048)
				return true;
	return false;
}

/**
 * @brief Checks if a move is valid and updates the game state.
 */
void Board::checkMove()
{
	if (!this->isEqual()) {
		if (this->newCell()) {
			u64* temp = new u64[size * size];
			for (u32 i = 0; i < size; i++)
				for (u32 j = 0; j < size; j++)
					temp[i * size + j] = this->cells[i][j].getValue();
			undoBoardStack.push(temp, size * size);
			delete[] temp;
			temp = nullptr;

			undoScoreStack.push(score);
		}
	}
	if (isWin()) {
		std::cout << "You Win\n";
	}
	else if (isOver()) {
		std::cout << "Game Over\n";
	} else 
		std::cout << "Game is playing\n";
}

/**
 * @brief Adds a new cell to the board.
 */
bool Board::newCell() {
	bool flag = false;
	/* Check there are a 0-value cell */
	for (u32 i = 0; i < size; i++) {
		for (u32 j = 0; j < size; j++) {
			if (this->cells[i][j].getValue() == 0) {
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}
	if (!flag)
		return false;

	int x, y;
	u64 value = static_cast<u64>(Random<u32>(1, 2)) * 2;
	while (true) {
		x = rand() % size;
		y = rand() % size;
		if (this->cells[x][y].getValue() == 0) {
			this->cells[x][y].setValue(value);
			break;
		}
	}

	cells[x][y].isNew = true;

	return true;
}

/**
 * @brief Resets the merge flags of all cells to false.
 */
void Board::resetMergeFlags()
{
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			this->cells[i][j].isMerged = false;
}

/**
* @brief Moves the cells up.
*/
void Board::UpMove() {
	this->resetMergeFlags();
	for (int i = 0; i < (s32)size; i++) {
		for (int j = 1; j < (s32)size; j++) {
			if (this->cells[i][j].getValue() != 0) {
				int y = j - 1;
				while (y >= 0 && this->cells[i][y].getValue() == 0)
					y--;
				if (y != -1 && this->cells[i][y].getValue() == this->cells[i][j].getValue() && !this->cells[i][y].isMerged) {
					this->cells[i][y].setValue(this->cells[i][y].getValue() * 2);
					score += this->cells[i][y].getValue();
					this->cells[i][y].isMerged = true;
					this->cells[i][j].setValue(0);
				}
				else if (y != j - 1) {
					this->cells[i][y + 1].setValue(this->cells[i][j].getValue());
					this->cells[i][j].setValue(0);
				}
			}
		}
	}
}

/**
* @brief Moves the cells down.
*/
void Board::DownMove() {
	this->resetMergeFlags();
	for (int i = 0; i < (s32)size; i++) {
		for (int j = (s32)size - 2; j >= 0; j--) {
			if (this->cells[i][j].getValue() != 0) {
				int y = j + 1;
				while (y < (s32)size && this->cells[i][y].getValue() == 0) {
					y++;
				}
				if (y != size && this->cells[i][y].getValue() == this->cells[i][j].getValue() && !this->cells[i][y].isMerged) {
					this->cells[i][y].setValue(this->cells[i][y].getValue() * 2);
					score += this->cells[i][y].getValue();
					this->cells[i][y].isMerged = true;
					this->cells[i][j].setValue(0);
				}
				else if (y != j + 1) {
					this->cells[i][y - 1].setValue(this->cells[i][j].getValue());
					this->cells[i][j].setValue(0);
				}
			}
		}
	}
}

/**
* @brief Moves the cells left.
*/
void Board::LeftMove() {
	this->resetMergeFlags();
	for (int j = 0; j < (s32)size; j++) {
		for (int i = 1; i < (s32)size; i++) {
			if (this->cells[i][j].getValue() != 0) {
				int x = i - 1;
				while (x >= 0 && this->cells[x][j].getValue() == 0) {
					x--;
				}
				if (x != -1 && this->cells[x][j].getValue() == this->cells[i][j].getValue() && !this->cells[x][j].isMerged) {
					this->cells[x][j].setValue(this->cells[x][j].getValue() * 2);
					score += this->cells[x][j].getValue();
					this->cells[x][j].isMerged = true;
					this->cells[i][j].setValue(0);
				}
				else if (x != i - 1) {
					this->cells[x + 1][j].setValue(this->cells[i][j].getValue());
					this->cells[i][j].setValue(0);
				}
			}
		}
	}
}

/**
* @brief Moves the cells right.
*/
void Board::RightMove() {
	this->resetMergeFlags();
	for (int j = 0; j < (s32)size; j++) {
		for (int i = (s32)size - 2; i >= 0; i--) {
			if (this->cells[i][j].getValue() != 0) {
				int x = i + 1;
				while (x < (s32)size && this->cells[x][j].getValue() == 0) {
					x++;
				}
				if (x != size && this->cells[x][j].getValue() == this->cells[i][j].getValue() && !this->cells[x][j].isMerged) {
					this->cells[x][j].setValue(this->cells[x][j].getValue() * 2);
					score += this->cells[x][j].getValue();
					this->cells[x][j].isMerged = true;
					this->cells[i][j].setValue(0);
				}
				else if (x != i + 1) {
					this->cells[x - 1][j].setValue(this->cells[i][j].getValue());
					this->cells[i][j].setValue(0);
				}
			}
		}
	}
}


/**
 * @brief Undoes the last move.
 */
void Board::Undo()
{
	if (undoBoardStack.empty()) {
		std::cout << "UndoBoardStack is empty\n";
		return;
	}

	u64* temp = undoBoardStack.top();
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			this->cells[i][j].setValue(temp[i * size + j]);
	redoBoardStack.push(temp, size * size);
	undoBoardStack.pop();

	if (undoScoreStack.empty()) {
		std::cout << "UndoScoreStack is empty\n";
		return;
	}
	score = undoScoreStack.top();
	redoScoreStack.push(score);
	undoScoreStack.pop();
}

/**
 * @brief Redoes the last undone move.
 */
void Board::Redo()
{
	if (redoBoardStack.empty()) {
		std::cout << "RedoBoardStack is empty\n";
		return;
	}
	u64* temp = redoBoardStack.top();
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			this->cells[i][j].setValue(temp[i * size + j]);
	undoBoardStack.push(temp, size * size);
	redoBoardStack.pop();

	score = redoScoreStack.top();
	undoScoreStack.push(score);
	redoScoreStack.pop();
}

/**
* @brief Clears the undo stack of board.
*/
void Board::clearUndoBoardStack()
{
	while (!undoBoardStack.empty())
		undoBoardStack.pop();
}

/**
* @brief Clears the redo stack of board.
*/
void Board::clearRedoBoardStack()
{
	while (!redoBoardStack.empty())
		redoBoardStack.pop();
}

/**
*@brief Clears undo stack of score.
*/
void Board::clearUndoScoreStack()
{
	while (!undoScoreStack.empty())
		undoScoreStack.pop();
}

/**
*@brief Clears redo stack of score.
*/
void Board::clearRedoScoreStack()
{
	while (!redoScoreStack.empty())
		redoScoreStack.pop();
}

void Board::clear()
{
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			this->cells[i][j].setValue(0);
}

/**
 * @brief Updates the game state.
 * @param deltaTime The time since the last update.
 */
void Board::update(float deltaTime) {
	pressTime -= deltaTime;

	if (pressTime <= 0.0f && canMove) {

		if (!OnOffStack) { // If board turn off stack
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				pressTime = PRESS_DELAY;
				this->clearNewCells();
				this->UpMove();
				this->checkMove();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				pressTime = PRESS_DELAY;
				this->clearNewCells();
				this->DownMove();
				this->checkMove();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				pressTime = PRESS_DELAY;
				this->clearNewCells();
				this->LeftMove();
				this->checkMove();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				pressTime = PRESS_DELAY;
				this->clearNewCells();
				this->RightMove();
				this->checkMove();
			}
		}
		else { // If board turn on stack
			if (!isUndo && !isRedo) { // If not undo or redo state
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					this->UpMove();
					this->checkMove();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					this->DownMove();
					this->checkMove();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					this->LeftMove();
					this->checkMove();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					this->RightMove();
					this->checkMove();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					isUndo = true;
					isRedo = false;
					undoBoardStack.pop();
					undoScoreStack.pop();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					isUndo = false;
					isRedo = true;
					redoBoardStack.pop();
					redoScoreStack.pop();
				}
			}
			else if (isUndo && !isRedo) { // If board is in undo state
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					this->clearRedoBoardStack();
					this->clearRedoScoreStack();
					isUndo = false;
					isRedo = false;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						this->UpMove();
						this->checkMove();
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						this->DownMove();
						this->checkMove();
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
						this->LeftMove();
						this->checkMove();
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
						this->RightMove();
						this->checkMove();
					}

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					isUndo = true;
					isRedo = false;
					this->Undo();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					isUndo = false;
					isRedo = true;
					this->Redo();
				}
			}
			else if (!isUndo && isRedo) { // If board is in redo state
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					pressTime = PRESS_DELAY;
					this->clearNewCells();
					this->clearRedoBoardStack();
					this->clearRedoScoreStack();
					isUndo = false;
					isRedo = false;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						this->UpMove();
						this->checkMove();
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						this->DownMove();
						this->checkMove();
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
						this->LeftMove();
						this->checkMove();
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
						this->RightMove();
						this->checkMove();
					}

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
					pressTime = PRESS_DELAY;
					isUndo = true;
					isRedo = false;
					this->Undo();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
					pressTime = PRESS_DELAY;
					isUndo = false;
					isRedo = true;
					this->Redo();
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
			pressTime = PRESS_DELAY;
			std::cout << "UNDO\n";
			undoBoardStack.print(size);
			undoScoreStack.print();
			std::cout << "REDO\n";
			redoBoardStack.print(size);
			redoScoreStack.print();
		}

	}
}

/**
* @brief Clears the new cells.
*/
void Board::clearNewCells()
{
	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			this->cells[i][j].isNew = false;
}

/**
 * @brief Draws the board.
 * @param rt The render target to draw to.
 * @param rs The render states to use.
 */
void Board::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	rt.draw(backgroundPlaying, rs); // Draw background
	rt.draw(border, rs); // Draw table

	for (u32 i = 0; i < size; i++)
		for (u32 j = 0; j < size; j++)
			rt.draw(this->cells[i][j], rs); // Draw this->cells
}
