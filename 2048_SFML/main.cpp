#include "UI.hpp"
#include "Top20List.hpp"
#include "Music.hpp"

/**
 * Entry point of the application.
 */
int main() {

    // Load and set the application icon
    sf::RenderWindow window(sf::VideoMode(Game::GAME_WIDTH, Game::GAME_HEIGHT), "2048",
        sf::Style::Titlebar | sf::Style::Close);
    sf::Image icon;
    if (!icon.loadFromFile("Texture/appIcon.png")) {
        std::cout << "Could not load image\n";
        return 0;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);

    sf::Event event;
    sf::Clock clock;

    // Initialize game objects
    Music music("Music");
    UI ui;
   

    // Main game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Event polling
        while (window.pollEvent(event)) {
            auto pos = sf::Mouse::getPosition(window);

            // Handle window close event
            if (event.type == sf::Event::Closed) {
                ui.saveData();
                window.close();
                break;
            }
            music.handleEvent(event);
            ui.handleEvent(deltaTime, event, pos);
        }

        ui.update(deltaTime);
        window.draw(ui);
        ui.sendMessage(window);

        window.display();
    }
    return 0;
}
