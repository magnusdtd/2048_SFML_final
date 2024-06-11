#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include "Board.hpp"
#include <chrono>
#include <ctime>
#include "Login.hpp"
#include "PlayerList.hpp"

/**
 * UI class is responsible for managing the user interface of the game.
 * It handles the game states and updates the UI accordingly.
 */
class UI : public sf::Drawable {
private:
    /* Common */
    sf::Font font;  // Font used in the UI
    const float PRESS_DELAY = 0.4f;  // Delay between key presses
    float pressTime;  // Time since last key press
    Game::State state = Game::START_MENU;  // Current game state

    /* Start Menu */
    sf::Texture backgroundTextureStartMenu;  // Texture for start menu background
    sf::Sprite backgroundStartMenu;  // Sprite for start menu background
    u32 SELECT_BUTTON;  // Currently selected button in the start menu
    sf::Text ButtonNewGame;  // New Game button
    sf::Text ButtonSetting;  // Settings button
    sf::Text ButtonTop20List;  // Top 20 List button
    sf::Text ButtonResume;  // Resume button

    /* Setting */
    sf::Texture backgroundTextureSetting;  // Texture for settings background
    sf::Sprite backgroundSetting;  // Sprite for settings background
    u32 whichButton;  // Currently selected button in the settings

    Game::Mode mode;  // Current game mode (4x4, 5x5, 6x6, 7x7, 8x8, 9x9, 10x10)
    u32 buttonMode;  // Currently selected mode button
    sf::Text textMode;  // Text displaying the current mode

    u32 buttonOnOff;  // Button for turning on/off a feature
    sf::Text textOnOff;  // Text displaying the on/off status

    /* Resume */
    sf::Texture backgroundTextureResume;  // Texture for resume background
    sf::Sprite backgroundResume;  // Sprite for resume background

    /* Playing */
    sf::Texture backgroundTexturePlaying;  // Texture for playing background
    sf::Sprite backgroundPlaying;  // Sprite for playing background
    sf::Text textBestScore;  // Text displaying the best score
    sf::Text textScore;  // Text displaying the current score
    sf::Text textGameOver;  // Text displaying game over message
    sf::Text textWin;  // Text displaying win message
    sf::Text subMessage;  // Sub message
    u64 bestScore = 0;  // Best score
    u64 score = 0;  // Current score
    bool newScore = false;  // Flag indicating if a new score has been achieved
    bool isGameOver = false;  // Flag indicating if the game is over
    bool isWin = false;  // Flag indicating if the player has wond

    //
    bool isCanUndo = true;  // Flag indicating if the player can undo a move
    bool isCanCheckMove = true;  // Flag indicating if the game can check for a move
    //

    bool isCalculated = false;  // Flag indicating if the time has been calculated
    std::chrono::system_clock::time_point startTime; ///< Start time for the game
    std::chrono::system_clock::time_point endTime; ///< Start time for the game

    Player player;  // Player object
public:
    /**
     * Constructor for the UI class.
     * Initializes the UI elements.
     */
    UI();

    /**
    * @return the player object for playlist to store it.
    */
    Player getPlayer() const;

    /**
     * Returns the current game state.
     * @return Current game state
     */
    Game::State getState() const;

    /**
    * Loads the best score from a file.
    */
    u64 loadBestScore(std::string filename);

    /**
    * Saves the best score to a file.
	*/
    void saveBestScore(std::string filename) const;

    /**
     * Handles the game over state.
     * Checks if a new score has been achieved and saves it if necessary.
     */
    void GameOverMessage(u64 position);

    /**
     * Handles the win state.
     * Checks if a new score has been achieved and saves it if necessary.
     */
    void WinMessage(u64 position);

    /**
     * Updates the UI based on the current game state.
     * @param deltaTime Time since the last frame
     * @param board Reference to the game board
     * @param tf Reference to the text field
     */
    void update(float deltaTime, Board& board, Login& login, PlayerList& playerList);

    /**
     * Draws the UI elements on the screen.
     * @param rt Render target to draw on
     * @param rs Current render states
     */
    void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;

    /**
    * Sends a message to the window.
    */
    void sendMessage(sf::RenderWindow& window);
};

#endif
