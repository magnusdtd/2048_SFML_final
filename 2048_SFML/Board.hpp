#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include "BoardStack.hpp"
#include "ScoreStack.hpp"
#include "Cell.hpp"

/**
 * @class Board
 * @brief This class represents the game board.
 *
 * The Board class is responsible for managing the game state, including the cells, score, and game rules.
 */
class Board : public sf::Drawable {
private:
	Cell **cells; ///< 2D array of cells
	sf::Font font; ///< Font used for rendering text

	const float PRESS_DELAY = 0.3f; ///< Delay between key presses
	float pressTime; ///< Time since last key press

	sf::Texture backgroundTexturePlaying;  // Texture for playing background
	sf::Sprite backgroundPlaying;  // Sprite for playing background
	sf::Texture borderTexture; ///< Texture for the border
	sf::Sprite border; ///< Sprite for the border

	BoardStack undoBoardStack; ///< Stack for undo operations
	BoardStack redoBoardStack; ///< Stack for redo operations
	ScoreStack undoScoreStack; ///< Stack for undo operations
	ScoreStack redoScoreStack; ///< Stack for redo operations

	bool isUndo; ///< Boolean to check if undo is possible
	bool isRedo; ///< Boolean to check if redo is possible
public:
	u64 score; ///< Current score
	u32 size; ///< Size of the board
	bool OnOffStack; ///< Boolean to check if undo/redo is on or off
	bool canMove; ///< Boolean to pause the game

	/**
	 * @brief Default constructor for Board.
	 */
	Board();

	/**
	 * @brief Destructor for Board.
	 */
	~Board();

	/**
	 * @brief Initializes the board.
	 */
	void init(	u32 width,
				u32 height,
				u32 size,
				float sizeOfEachCell,
				float distanceBetweenEachCell,
				float distanceBetweenCellAndBorder,
				float alignX,
				float alignY,
				u32 sizeofValue, 
				float alignNewText,
				u32 sizeOfNewText);

	/**
	 * @brief Checks if the board state is equal to the previous state.
	 * @return True if the board state is equal to the previous state, false otherwise.
	 */
	bool isEqual();

	/**
	 * @brief Checks if the game is over.
	 * @return True if the game is over, false otherwise.
	 */
	bool isOver();

	/**
	 * @brief Checks if the player has won the game.
	 * @return True if the player has won, false otherwise.
	 */
	bool isWin();

	/**
	 * @brief Checks if a move is valid and updates the game state.
	 */
	void checkMove();

	/**
	 * @brief Adds a new cell to the board.
	 * @return True if a new cell was added, false otherwise.
	 */
	bool newCell();

	/**
	* Reset the hasMerged flag of all cells to false.
	*/
	void resetMergeFlags();

	/**
	 * @brief Moves the cells up.
	 */
	void UpMove();

	/**
	 * @brief Moves the cells down.
	 */
	void DownMove();

	/**
	 * @brief Moves the cells left.
	 */
	void LeftMove();

	/**
	 * @brief Moves the cells right.
	 */
	void RightMove();

	/**
	 * @brief Undoes the last move.
	 */
	void Undo();

	/**
	 * @brief Redoes the last undone move.
	 */
	void Redo();

	/**
	* @brief Clears the undo stack of board.
	*/
	void clearUndoBoardStack();

	/**
	* @brief Clears the redo stack of board.
	*/
	void clearRedoBoardStack();

	/**
	*@brief Clears undo stack of score.
	*/
	void clearUndoScoreStack();

	/**
	*@brief Clears redo stack of score.
	*/
	void clearRedoScoreStack();

	/**
	* Clears the board.
	*/
	void clear();

	/**
	 * @brief Updates the game state.
	 * @param deltaTime The time since the last update.
	 */
	void update(float deltaTime);

	/**
	* @brief Clears the new cells.
	*/
	void clearNewCells();

	/**
	 * @brief Draws the board.
	 * @param rt The render target to draw to.
	 * @param rs The render states to use.
	 */
	void draw(sf::RenderTarget& rt, sf::RenderStates rs) const override;
};

#endif