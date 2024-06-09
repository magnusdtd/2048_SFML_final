#include "UI.hpp"
#include "PlayerList.hpp"
#include "RSA.hpp"

void test() {
    RSA security(211, 199);

    std::string msg = "Toi ten la";
    u64* encrypted = security.encryptString(msg);
    std::string decrypted = security.decryptString(encrypted, msg.size());

    std::cout << "Encrypted: ";
    for (u32 i = 0; i < msg.size(); i++) {
        std::cout << encrypted[i] << ' ';
    }
    std::cout << "\n";

    std::cout << "Decrypted: " << decrypted << "\n";


    delete[] encrypted;
    encrypted = nullptr;
}


/**
 * Entry point of the application.
 */
int main() {

    test();

    std::cout << "Press any key to continue...\n";

    // Create a window with specific properties
    sf::RenderWindow window(sf::VideoMode(Game::GAME_WIDTH, Game::GAME_HEIGHT), "2048",
        sf::Style::Titlebar | sf::Style::Close);

    // Load and set the application icon
    auto image = sf::Image{};
    if (!image.loadFromFile("Texture/appIcon.png")) {
        std::cout << "Could not load image\n";
        return 0;
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    window.setFramerateLimit(60);

    sf::Event event;
    sf::Clock clock;

    // Initialize game objects
    Board board;
    UI ui;
    TextField textfield(20, 500.f, 36.f);
    textfield.setPosition(300.f, 420.f);
    textfield.setFocus(true);
    PlayerList playerList;
    //playerList.loadData("Data/player_name.dat", "Data/player_score.dat", "Data/player_time.dat");


    // Main game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Event polling
        while (window.pollEvent(event)) {
            // Handle window close event
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            // Handle mouse button release event
            else if (event.type == sf::Event::MouseButtonReleased) {
                auto pos = sf::Mouse::getPosition(window);
                textfield.setFocus(false);
                if (textfield.contains(sf::Vector2f(pos)))
                    textfield.setFocus(true);
            }
            // Handle text input event
            else if (event.type == sf::Event::TextEntered && ui.getState() == Game::REGISTER)
                textfield.handleInput(event, deltaTime);

        }

        // Update UI and draw it on the window
        ui.update(deltaTime, board, textfield);
        window.draw(ui);

        // Draw textfield or board based on the game state
        if (ui.getState() == Game::REGISTER) {
            window.draw(textfield);
        }
        else if (ui.getState() == Game::PLAYING) {
            board.update(deltaTime);
            window.draw(board);
        }

        // Display the window content
        ui.sendMessage(window);

        // Display the window content
        window.display();
    }
    return 0;
}
