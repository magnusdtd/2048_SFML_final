#ifndef SETTING_HPP
#define SETTING_HPP

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "layout.hpp"
#include <iostream>

class Setting : public sf::Drawable {
    sf::Texture backgroundTextureSetting;  // Texture for settings background
    sf::Sprite backgroundSetting;  // Sprite for settings background
    u32 whichButton;  // Currently selected button in the settings

    u32 buttonMode;  // Currently selected mode button
    sf::Text textMode;  // Text displaying the current mode

    u32 buttonOnOff;  // Button for turning on/off a feature
    sf::Text textOnOff;  // Text displaying the on/off status

	sf::Font font;
    float pressTime;
    const float PRESS_DELAY = 0.4f;
public:
    bool canUndoRedo;
    Game::Mode mode;  // Current game mode (4x4, 5x5, 6x6, 7x7, 8x8, 9x9, 10x10)

    Setting();

    void update(float deltaTime);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif