#include "UI.hpp"
#include "Board.hpp"
#include "layout.hpp"

int main() {
    // Window property
    sf::RenderWindow window(sf::VideoMode(Game::GAME_WIDTH, Game::GAME_HEIGHT), "2048",
                            sf::Style::Titlebar | sf::Style::Close);

    // Set icon
    auto image = sf::Image{};
    if (!image.loadFromFile("Texture/appIcon.png")) {
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
    TextField textfield(20, 500.f, 36.f);
    textfield.setPosition(300.f, 420.f);
    textfield.setFocus(true);
    
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
                textfield.setFocus(false);
                if (textfield.contains(sf::Vector2f(pos)))
                    textfield.setFocus(true);
            }
            else if (event.type == sf::Event::TextEntered && ui.getState() == Game::REGISTER)
                textfield.handleInput(event, deltaTime);
            
        }

        // Update
        ui.update(deltaTime, board, textfield);
        window.draw(ui);

        if (ui.getState() == Game::REGISTER) {;
			window.draw(textfield);
		}
        else if (ui.getState() == Game::PLAYING) {
            board.update(deltaTime);
            window.draw(board);
        }
 
        window.display(); // Tell app that window is done drawing
    }
    return 0;
}
