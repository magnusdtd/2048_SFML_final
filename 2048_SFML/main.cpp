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
            else if (event.type == sf::Event::KeyPressed) {
                // If the current track has stopped playing, switch to the next track
                if (music.getStatus() == sf::SoundSource::Status::Stopped) {
                    music.next();
                }
                if (event.key.code == sf::Keyboard::Slash) {
                    // Toggle play/pause when '/' is pressed
                    if (music.getStatus() == sf::Music::Playing)
                        music.pause();
                    else
                        music.play();
                }
                else if (event.key.code == sf::Keyboard::Comma)
                    // Switch to previous track when '<' (Comma key without Shift) is pressed
                    music.previous();
                else if (event.key.code == sf::Keyboard::Period)
                    // Switch to next track when '>' (Period key without Shift) is pressed
                    music.next();
                else if (event.key.code == sf::Keyboard::Add) {
                    // Increase volume when '+' is pressed
                    float volume = music.getVolume();
                    if (volume < 100.0f) {
                        volume += 10.0f;
                        music.setVolume(volume);
                    }
                }
                else if (event.key.code == sf::Keyboard::Subtract) {
                    // Decrease volume when '-' is pressed
                    float volume = music.getVolume();
                    if (volume > 0.0f) {
                        volume -= 10.0f;
                        music.setVolume(volume);
                    }
                }
            }
            ui.handleEvent(deltaTime, event, pos);
        }

        auto state = ui.getState();
        if (state == Game::TOP20LIST)
            ui.update(deltaTime);
        else {
            window.setView(window.getDefaultView());
            ui.update(deltaTime);
            window.draw(ui);
        }


        ui.sendMessage(window);

        window.display();
    }
    return 0;
}
