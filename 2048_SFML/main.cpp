#include "UI.hpp"
#include "RSA.hpp"
#include "BigInteger.hpp"
#include "Top20List.hpp"
#include "Resume.hpp"
#include "Music.hpp"

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
    for (int i = 0; i < 10; i++) {
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
    Board board;
    UI ui;
    Login login;
    Top20List top20List;
    PlayerList playerList;
    /*playerList.clearDataFile("Data/player_name.dat",
                            "Data/player_score.dat",
                            "Data/player_time.dat",
                            "Data/player_password.dat");*/
    playerList.loadData("Data/player_name.dat", 
                        "Data/player_score.dat", 
                        "Data/player_time.dat", 
                        "Data/player_password.dat");
    //test3(playerList);
    Resume resume;

    // Main game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Event polling
        while (window.pollEvent(event)) {
            // Handle window close event
            if (event.type == sf::Event::Closed) {
                Player player = ui.getPlayer();
                if (playerList.getPlayer(player.getName()) == nullptr && 
                    player.getName() != "" && 
                    player.getScore() != 0 &&
                    player.getTime() != 0)
                    playerList.addPlayer(player);
                playerList.writeMaxScore("Data/best_score.dat");
                playerList.saveData("Data/player_name.dat",
                                    "Data/player_score.dat",
                                    "Data/player_time.dat",
                                    "Data/player_password.dat");
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
            login.handleInput(event, window, ui.getState(), deltaTime);
            resume.handleInput(event, window, ui.getState(), deltaTime);
        }

        auto state = ui.getState();
        if (state == Game::TOP20LIST) {
            ui.update(deltaTime, board, login, playerList, resume);
            top20List.update(deltaTime, playerList);
            top20List.draw(window, playerList);
        }
        else {
            window.setView(window.getDefaultView());
            ui.update(deltaTime, board, login, playerList, resume);
            window.draw(ui);
        }


        if (state == Game::REGISTER)
            window.draw(login);
        else if (state == Game::PLAYING) {
            board.update(deltaTime);
            window.draw(board);
        }
        else if (state == Game::RESUME) {
            resume.update(deltaTime);
            resume.draw(window);
        }


        ui.sendMessage(window);

        window.display();
    }
    return 0;
}
