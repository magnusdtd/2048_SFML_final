#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "utils.hpp"
#include "SFML/Graphics.hpp"
#include <array>

#define BEST_SCORE_FILE "Data/best_score.dat"
#define PLAYER_NAME_FILE "Data/player_name.dat"
#define PLAYER_SCORE_FILE "Data/player_score.dat"
#define PLAYER_TIME_FILE "Data/player_time.dat"

namespace Game {
    enum State {
        START_MENU,
        SETTING,
        REGISTER,
        TOP20LIST,
        PLAYING,
    };

    enum Mode {
        MODE_4 = 4,
        MODE_5,
        MODE_6,
        MODE_7,
        MODE_8,
        MODE_9,
        MODE_10
    };

    enum StartMenuButton {
        NewGame,
        Setting,
        Top20List,
        Resume,
        NUMBER_OF_BUTTONS
    };

    static u32 GAME_WIDTH = 1200;
    static u32 GAME_HEIGHT = 800;
}

class Layout {
public:
    u32 boardSize;
    float sizeOfEachCell;
    float distanceBetweenEachCell;
    float distanceBetweenCellAndBorder;
    float alignX; // distance between cell and score in x axis
    float alignY; // distance between cell and score in y axis
    u32 sizeOfValue;
};

namespace LAYOUT {
    static Layout LAYOUT_4 = { 4, 170.f, 5.f, 20.f, 82.f, 78.f, 40 };
    static Layout LAYOUT_5 = { 5, 125.f, 5.f, 20.f, 62.f, 54.f, 35 };
    static Layout LAYOUT_6 = { 6, 100.f, 5.f, 20.f, 46.f, 40.f, 30 };
    static Layout LAYOUT_7 = { 7, 90.f, 5.f, 20.f, 42.f, 36.f, 27 };
    static Layout LAYOUT_8 = { 8, 75.f, 5.f, 20.f, 35.f, 31.f, 22 };
    static Layout LAYOUT_9 = { 9, 70.f, 5.f, 20.f, 32.f, 28.f, 20 };
    static Layout LAYOUT_10 = { 10, 60.f, 5.f, 20.f, 28.f, 25.f, 18 };
}

namespace Color {
    static std::array<sf::Color, 12> colors = { sf::Color(102,102,102),
                                                sf::Color(255,166,0),
                                                sf::Color(245,151,245),
                                                sf::Color(51,204,153),
                                                sf::Color(255,110,110),
                                                sf::Color(255,204,77),
                                                sf::Color(166,166,255),
                                                sf::Color(137,194,247),
                                                sf::Color(0,255,255),
                                                sf::Color(0,128,0),
                                                sf::Color(255,0,255),
                                                sf::Color(128,128,0) };
}

#endif
