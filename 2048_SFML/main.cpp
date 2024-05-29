#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Game.hpp"
#include "Board.hpp"
#include "UI.hpp"

int main() {
    // Window property
    sf::RenderWindow window(sf::VideoMode(Game::GAME_WIDTH, Game::GAME_HEIGHT), "2048",
                        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    auto image = sf::Image{};
    if (!image.loadFromFile("resources/appIcon.png")) {
        std::cout << "Could not load image\n";
        return 0;
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    window.setFramerateLimit(60);

    sf::Event event;
    sf::Clock clock;

    Board board;
    UI ui;
    
    // Game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
          
        // Event polling
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        // Update
        window.clear(sf::Color::White);

        /*board.update(deltaTime);
        ui.update(deltaTime, board.getScore());*/

        // Render
        /*window.draw(ui);
        window.draw(board);*/

        window.display(); // Tell app that window is done drawing
    }

    return 0;
}
