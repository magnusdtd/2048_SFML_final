#ifndef START_MENU_HPP
#define START_MENU_HPP

#include "SFML/Graphics.hpp"
#include "utils.hpp"
#include "layout.hpp"
#include <iostream>

class StartMenu : public sf::Drawable{
    sf::Texture backgroundTextureStartMenu;  // Texture for start menu background
    sf::Sprite backgroundStartMenu;  // Sprite for start menu background

    sf::Text ButtonNewGame;  // New Game button
    sf::Text ButtonSetting;  // Settings button
    sf::Text ButtonTop20List;  // Top 20 List button
    sf::Text ButtonResume;  // Resume button

    sf::Font font;
    float pressTime;
    const float PRESS_DELAY = 0.4f;
public:
    u32 SELECT_BUTTON;  // Currently selected button in the start menu

    StartMenu();

    void update(float deltaTime);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif

