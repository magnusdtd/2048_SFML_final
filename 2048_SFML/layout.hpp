#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "utils.hpp"
#include "SFML/Graphics.hpp"
#include <array>

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

struct Layout {
    u32 boardSize;
    float sizeOfEachCell;
    float distanceBetweenEachCell;
    float distanceBetweenCellAndBorder;
    float distanceBetweenCellAndScore;
    u32 sizeOfValue;
};

namespace LAYOUT {
    static Layout LAYOUT_4 = { 4, 170.f, 5.f, 20.f, 65.f, 40 };
    static Layout LAYOUT_5 = { 5, 125.f, 5.f, 20.f, 0.f, 20 };
    static Layout LAYOUT_6 = { 6, 100.f, 5.f, 20.f, 10.f, 50 };
    static Layout LAYOUT_7 = { 7, 90.f, 5.f, 20.f, 10.f, 50 };
    static Layout LAYOUT_8 = { 8, 75.f, 5.f, 20.f, 10.f, 50 };
    static Layout LAYOUT_9 = { 9, 70.f, 5.f, 20.f, 10.f, 50 };
    static Layout LAYOUT_10 = { 10, 60.f, 5.f, 20.f, 10.f, 50 };
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
