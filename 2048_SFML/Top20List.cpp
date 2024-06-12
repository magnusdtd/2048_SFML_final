#include "Top20List.hpp"

Top20List::Top20List()
    : view(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT)) {
    viewBoundary = sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT);
    backgroundTextureTop20List.loadFromFile("Texture/Top20List.png");
    backgroundTop20List.setTexture(backgroundTextureTop20List);
}

void Top20List::update(float deltaTime, PlayerList& playerList)
{
    pressTime -= deltaTime;
    if (pressTime < 0.0f) pressTime = 0.0f;

    newPosition = view.getCenter();

    // Adjust the view boundary based on the number of players
    viewBoundary.height = 400.f + playerList.getSize() * 120.f - 500.f;
    if (viewBoundary.height > 2825.f) 
        viewBoundary.height = 2825.f;

    if (newPosition.y <= 400)
        newPosition.y = 400;
    else if (newPosition.y >= viewBoundary.height)
        newPosition.y = viewBoundary.height;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.0f) {
        pressTime = 0.1f;
        newPosition.y += moveSpeed * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.0f && newPosition.y > 400) {
        pressTime = 0.1f;
        newPosition.y -= moveSpeed * deltaTime;
    }

    // Check if the new position is within the boundary
    if (viewBoundary.contains(newPosition))
        view.setCenter(newPosition);
}

void Top20List::draw(sf::RenderWindow& window, PlayerList& playerList) const
{
    window.setView(view);
    window.draw(backgroundTop20List);
    playerList.showList(window, 20);
}