#pragma once

#include <SFML/Graphics.hpp>
#include "PlayerList.hpp"
#include "layout.hpp"

class Top20List {
private:
    sf::Texture backgroundTextureTop20List;  // Texture for top 20 list background
    sf::Sprite backgroundTop20List;  // Sprite for top 20 list background

    sf::View view;
    sf::FloatRect viewBoundary;
    sf::Vector2f newPosition;
    const float moveSpeed = 2500.0f;
    float pressTime = 0.f;

public:
    Top20List();

    void update(float deltaTime, PlayerList& playerList);

    void draw(sf::RenderWindow& window, PlayerList& playerList) const;
};


