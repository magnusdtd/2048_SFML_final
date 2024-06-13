#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "utils.hpp"
#include "SFML/Graphics.hpp"
#include <array>

// File paths for storing game data
#define BEST_SCORE_FILE "Data/best_score.dat"
#define PLAYER_NAME_FILE "Data/player_name.dat"
#define PLAYER_SCORE_FILE "Data/player_score.dat"
#define PLAYER_TIME_FILE "Data/player_time.dat"

namespace Game {
    // Enum representing the different states of the game
    enum State {
        START_MENU,
        SETTING,
        REGISTER,
        TOP20LIST,
        PLAYING,
        RESUME,
        INF 
    };

    // Enum representing the different modes of the game
    enum Mode {
        MODE_4 = 4,
        MODE_5,
        MODE_6,
        MODE_7,
        MODE_8,
        MODE_9,
        MODE_10
    };

    // Enum representing the different buttons in the start menu
    enum StartMenuButton {
        NewGame,
        Setting,
        Top20List,
        Resume,
        NUMBER_OF_BUTTONS
    };

    enum ResumeState {
        RESUME_OPTION, // The scenario that the player can choose to play again or register

        RESUME_LOGIN, // Login to the account when choosing to continue

        RESUME_PLAY, // Play the game

        RESUME_GO_BACK // Go back to the start menu
    };

    // Game window dimensions
    static u32 GAME_WIDTH = 1200;
    static u32 GAME_HEIGHT = 800;
}

// Class representing the layout of the game board
class Layout {
public:
    u32 boardSize; // Size of the game board
    float sizeOfEachCell; // Size of each cell in the game board
    float distanceBetweenEachCell; // Distance between each cell in the game board
    float distanceBetweenCellAndBorder; // Distance between each cell and the border of the game board
    float alignX; // Distance between cell and score in x axis
    float alignY; // Distance between cell and score in y axis
    u32 sizeOfValue; // Size of the value in each cell
    float alignNextText; // Alignment of the next text
    u32 sizeOfNextText; // Size of the next text
};

namespace LAYOUT {
    // Layout configurations for different game modes
    static Layout LAYOUT_4 = { 4, 170.f, 5.f, 20.f, 82.f, 78.f, 40, 10.f, 30 };
    static Layout LAYOUT_5 = { 5, 125.f, 5.f, 20.f, 62.f, 54.f, 35, 10.f, 25 };
    static Layout LAYOUT_6 = { 6, 100.f, 5.f, 20.f, 46.f, 40.f, 30, 10.f, 18 };
    static Layout LAYOUT_7 = { 7, 90.f, 5.f, 20.f, 42.f, 36.f, 27, 8.f, 15 };
    static Layout LAYOUT_8 = { 8, 75.f, 5.f, 20.f, 35.f, 31.f, 22, 8.f, 14 };
    static Layout LAYOUT_9 = { 9, 70.f, 5.f, 20.f, 32.f, 28.f, 20, 8.f, 12 };
    static Layout LAYOUT_10 = { 10, 60.f, 5.f, 20.f, 28.f, 25.f, 18, 5.f, 8 };
}

namespace Color {
    // Array of colors used in the game
    static sf::Color colors[12] = { sf::Color(102, 102, 102),
                                    sf::Color(255, 166, 0),
                                    sf::Color(246, 157, 227),
                                    sf::Color(51, 204, 153),
                                    sf::Color(255, 110, 110),
                                    sf::Color(255, 204, 77),
                                    sf::Color(166, 166, 255),
                                    sf::Color(137, 194, 247),
                                    sf::Color(0, 255, 255),
                                    sf::Color(34, 241, 34),
                                    sf::Color(209, 72, 244),
                                    sf::Color(232, 15, 15) };
}

#endif
