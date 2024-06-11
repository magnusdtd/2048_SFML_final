#include "UI.hpp"
#include "RSA.hpp"
#include "BigInteger.hpp"

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

void test2() {
    std::cout << "Test 2\n";
    BigInteger a("123456789");
    BigInteger b("987654321");
    std::cout << a << "\n";
    std::cout << b << "\n";
    std::cout << a + b << "\n";
    std::cout << a - b << "\n";

    std::cout << "Test 3\n";
    BigInteger c("-123456789");
    BigInteger d("-123456789");
    if (c == d) {
		std::cout << "Equal\n";
	}
	else {
		std::cout << "Not equal\n";
	}
    if (c >= d) {
		std::cout << "Greater or equal\n";
	}
	else {
		std::cout << "Less\n";
	}

}

void test3(PlayerList &playerList) {
    for (int i = 0; i < 20; i++) {
        playerList.addPlayer("Player" + std::to_string(i), (u64)Random<int>(0, 1000), Random<double>(0, 1000), "password");
    }
    std::cout << "Size: " << playerList.getSize() << "\n";
}


/**
 * Entry point of the application.
 */
int main() {

    test();
    test2();

    std::cout << "Press any key to continue...\n";

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
    sf::View view(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));
    sf::FloatRect viewBoundary(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT); // Define the boundary
    sf::Vector2f newPosition;

    const float moveSpeed = 2500.0f ; // Adjust this value to change the speed of the movement
    float pressTime = 0.f;

    // Initialize game objects
    Board board;
    UI ui;
    Login login;
    
    PlayerList playerList;
    /*playerList.clearDataFile("Data/player_name.dat",
                            "Data/player_score.dat",
                            "Data/player_time.dat",
                            "Data/player_password.dat");*/

    playerList.loadData("Data/player_name.dat", 
                        "Data/player_score.dat", 
                        "Data/player_time.dat", 
                        "Data/player_password.dat");
    test3(playerList);

    // Main game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        pressTime -= deltaTime;
        if (pressTime < 0.0f) pressTime = 0.0f;

        // Event polling
        while (window.pollEvent(event)) {
            // Handle window close event
            if (event.type == sf::Event::Closed) {
                playerList.saveData("Data/player_name.dat",
                    "Data/player_score.dat",
                    "Data/player_time.dat",
                    "Data/player_password.dat");
                window.close();
                break;
            }
            login.handleInput(event, window, ui.getState(), deltaTime);
        }

        auto state = ui.getState();
        if (state == Game::TOP20LIST) {
            newPosition = view.getCenter();

            // Adjust the view boundary based on the number of players
            viewBoundary.height = 400.f + playerList.getSize() * 120.f;
            if (viewBoundary.height > 2825.f) viewBoundary.height = 2825.f;

            if (newPosition.y <= 400) 
                newPosition.y = 400;
            else if (newPosition.y >= viewBoundary.height)
                newPosition.y = viewBoundary.height;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressTime <= 0.0f) {
                pressTime = 0.1f;
                newPosition.y += moveSpeed * deltaTime;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressTime <= 0.0f) {
                pressTime = 0.1f;
                newPosition.y -= moveSpeed * deltaTime;
            }

            // Check if the new position is within the boundary
            if (viewBoundary.contains(newPosition))
                view.setCenter(newPosition);

            window.setView(view);
            window.clear(sf::Color::White);
            ui.update(deltaTime, board, login, playerList);
            window.draw(ui);
            playerList.showList(window, 20);
        }
        else {
            window.setView(window.getDefaultView());
            ui.update(deltaTime, board, login, playerList);
            window.draw(ui);
        }


        // Draw textfield or board based on the game state
        if (state == Game::REGISTER)
            window.draw(login);
        else if (state == Game::PLAYING) {
            board.update(deltaTime);
            window.draw(board);
        }


        ui.sendMessage(window);

        window.display();
    }
    return 0;
}
