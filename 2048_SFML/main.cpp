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


/**
 * Entry point of the application.
 */
int main() {

    test();
    test2();

    std::cout << "Press any key to continue...\n";

  //  // Create a window with specific properties
  //  sf::RenderWindow window(sf::VideoMode(Game::GAME_WIDTH, Game::GAME_HEIGHT), "2048",
  //      sf::Style::Titlebar | sf::Style::Close);

  //  // Load and set the application icon
  //  auto image = sf::Image{};
  //  if (!image.loadFromFile("Texture/appIcon.png")) {
  //      std::cout << "Could not load image\n";
  //      return 0;
  //  }
  //  window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
  //  window.setFramerateLimit(60);

  //  sf::Event event;
  //  sf::Clock clock;

  //  // Initialize game objects
  //  Board board;
  //  UI ui;
  //  Login login;
  //  
  //  PlayerList playerList;
  //  playerList.loadData("Data/player_name.dat", 
  //                      "Data/player_score.dat", 
  //                      "Data/player_time.dat", 
  //                      "Data/player_password.dat");

  //  float pressTime = 0.f;

  //  // Main game loop
  //  while (window.isOpen()) {
  //      float deltaTime = clock.restart().asSeconds();

  //      pressTime -= deltaTime;

  //      // Event polling
  //      while (window.pollEvent(event)) {
  //          // Handle window close event
  //          if (event.type == sf::Event::Closed) {
  //              playerList.saveData("Data/player_name.dat", 
  //                                  "Data/player_score.dat", 
  //                                  "Data/player_time.dat", 
  //                                  "Data/player_password.dat");
  //              window.close();
  //              break;
  //          }
  //          login.handleInput(event, window, ui.getState(), deltaTime);
  //      }

  //      // Update UI and draw it on the window
  //      ui.update(deltaTime, board, login, playerList);
  //      window.draw(ui);

  //      // Draw textfield or board based on the game state
  //      if (ui.getState() == Game::REGISTER) {
  //          window.draw(login);
  //      }
  //      else if (ui.getState() == Game::PLAYING) {
  //          board.update(deltaTime);
  //          window.draw(board);
  //      }

  //      if (ui.getState() == Game::PLAYING && sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && pressTime <= 0.0f) {
  //          pressTime = 0.5f;
  //          std::cout << "_______________________Y pressed__________________\n";
		//	playerList.showTop20();
  //          std::cout << "__________________________________________________\n";
		//}
  //      // Display the window content
  //      ui.sendMessage(window);

  //      // Display the window content
  //      window.display();
  //  }
  //  return 0;
}
