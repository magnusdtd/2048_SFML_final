#include "Game.hpp"

void Game::StartGame(sf::RenderWindow& window) {
    sf::Texture backgroundTexture;
    sf::Sprite background;
    backgroundTexture.loadFromFile("resources/StartMenu.png");
    background.setTexture(backgroundTexture);
    background.setPosition(0.f, 0.f);

    window.draw(background);
}

void Game::Register(sf::RenderWindow& window, TextField& tf) {
    window.clear(sf::Color::White);

    tf.setPosition(Game::GAME_WIDTH / 2.f - 500.f / 2.f, Game::GAME_HEIGHT / 2.f - 30.f / 2.f);
    window.draw(tf);
    std::cout << tf.getText().size() << ": " << tf.getText() << "\n";
}

void Game::PlayGame(sf::RenderWindow& window, float deltaTime, Board& board, UI& ui) {
    window.clear(sf::Color::White);

    board.update(deltaTime);
    ui.update(deltaTime, board.getScore());
    window.draw(ui);
    window.draw(board);
}
