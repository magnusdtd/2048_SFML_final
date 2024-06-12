#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <chrono>
#include <ctime>
#include "Board.hpp"
#include "Login.hpp"
#include "PlayerList.hpp"
#include "Resume.hpp"
#include "Setting.hpp"
#include "StartMenu.hpp"
#include "Top20List.hpp"

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
    StartMenu startMenu;

    /* Setting */
    Setting setting;

    /* Register */
    Login login;

    /* Resume */
    Resume resume;

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

    /* Top 20 List */
    Top20List top20List;

    /* Board */
    Board board;

    PlayerList playerList;  // PlayerList object
    Player currentPlayer;  // Current player
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

    void handleEvent(float deltaTime, sf::Event event, sf::Vector2i position);

    /**
     * Updates the UI based on the current game state.
     * @param deltaTime Time since the last frame
     * @param board Reference to the game board
     * @param tf Reference to the text field
     */
    void update(float deltaTime);

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

    void saveData();
};

#endif
