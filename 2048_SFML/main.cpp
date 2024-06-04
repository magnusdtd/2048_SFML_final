#include "UI.hpp"
#include "Board.hpp"
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
    TextField tf(20, 500.f, 30.f);
    tf.setPosition(500.f, 300.f);
    
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
            }
            else if (event.type == sf::Event::TextEntered)
                tf.handleInput(event);
            
        }

        // Update
        ui.update(deltaTime, tf, board);
        board.update(deltaTime);

        window.draw(ui);
        if (ui.getState() == Game::PLAYING) 
               window.draw(board);
        if (ui.getState() == Game::REGISTER)
            window.draw(tf);

        window.display(); // Tell app that window is done drawing
    }
    return 0;
}
