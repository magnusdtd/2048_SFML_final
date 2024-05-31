#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Game.hpp"
#include "Board.hpp"
#include "UI.hpp"
#include "TextField.hpp"

int main() {
    // Window property
    sf::RenderWindow window(sf::VideoMode(Game::GAME_WIDTH, Game::GAME_HEIGHT), "2048",
                        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    // Set icon
    auto image = sf::Image{};
    if (!image.loadFromFile("resources/appIcon.png")) {
        std::cout << "Could not load image\n";
        return 0;
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    window.setFramerateLimit(60);

    sf::Event event;
    sf::Clock clock;

    // Game objects
    Board board;
    UI ui;

    // Test
    TextField tf(20, 500.f, 30.f);
    tf.setPosition(Game::GAME_WIDTH / 2.f - 500.f / 2.f, Game::GAME_HEIGHT / 2.f - 30.f / 2.f);

    sf::Texture backgroundTexture;
    sf::Sprite background;
    backgroundTexture.loadFromFile("resources/StartMenu.png");
    background.setTexture(backgroundTexture);
    background.setPosition(0.f, 0.f);
    
    // Game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
          
        // Event polling
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                auto pos = sf::Mouse::getPosition(window);
                tf.setFocus(false);
                if (tf.contains(sf::Vector2f(pos)))
                    tf.setFocus(true);
				/*else
					tf.setFocus(false);*/
            }
            else {
                tf.handleInput(event);
            }
        }

        // Update
        window.clear(sf::Color::White);

        /*board.update(deltaTime);
        ui.update(deltaTime, board.getScore());*/

        // Render
        /*window.draw(ui);
        window.draw(board);*/

        window.draw(background);
        window.draw(tf);
        std::cout << tf.getText().size() << ": " << tf.getText() << "\n";
        window.display(); // Tell app that window is done drawing
    }

    return 0;
}
