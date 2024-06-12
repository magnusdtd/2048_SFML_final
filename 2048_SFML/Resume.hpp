#ifndef RESUME_HPP
#define RESUME_HPP

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "PlayerList.hpp"
#include "TextField.hpp"
#include "layout.hpp"

class Resume : public sf::Drawable {
	float pressTime;  // Time since last key press
	const float PRESS_DELAY = 0.4f;  // Delay between key presses

	static const u32 MAX_PLAYERS = 5;
	u32 size;

    sf::Texture backgroundTextureResume;  // Texture for resume background
    sf::Sprite backgroundResume;  // Sprite for resume background
    sf::Font font;  // Font used in the resume

	sf::Text account1;  // Text displaying the first account
	sf::Text account2;  // Text displaying the second account
	sf::Text account3;  // Text displaying the third account
	sf::Text account4;  // Text displaying the fourth account
	sf::Text account5;  // Text displaying the fifth account
	sf::Text opt;
	Game::ResumeState state = Game::OPTION;  // Current resume state

	u64 SELECT_BUTTON;  // Currently selected button in the resume
	TextField userNameField;  // Username field
	TextField passwordField;  // Password field

public: 
	Resume();

	Game::ResumeState getState() const {
		return state;
	}

	Player * getSelectedPlayer();

	bool isMatchPassword();

	void handleInput(sf::Event event, sf::RenderWindow& window, Game::State state, float deltaTime);

	void addPlayer(std::string userName, u64 score, double timeToComplete, std::string password);

	void addPlayer(Player player);

	void update(float deltaTime);

	void draw(sf::RenderWindow& window);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif
