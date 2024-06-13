#ifndef RESUME_HPP
#define RESUME_HPP

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "PlayerList.hpp"
#include "TextField.hpp"
#include "layout.hpp"
#include "ResumeList.hpp"
#include "security.hpp"

class Resume : public sf::Drawable {
	float pressTime;  // Time since last key press
	const float PRESS_DELAY = 0.4f;  // Delay between key presses

	static const u32 MAX_PLAYERS = 5;  // Maximum number of players in the resume
	u32 size;  // Number of players in the resume

    sf::Texture backgroundTextureResume;  // Texture for resume background
    sf::Sprite backgroundResume;  // Sprite for resume background
    sf::Font textFont;  // Font used in the resume
	sf::Font titleFont;  // Font used in the resume

	/* RESUME_OPTION */
	sf::Text account1;  // Text displaying the first account
	sf::Text account2;  // Text displaying the second account
	sf::Text account3;  // Text displaying the third account
	sf::Text account4;  // Text displaying the fourth account
	sf::Text account5;  // Text displaying the fifth account

	/* RESUME_CONTINUE */
	sf::Texture backgroundTextureResumeContinueLogin;  // Texture for resume background
	sf::Sprite backgroundResumeLogin;  // Sprite for resume background

	TextField passwordField;  // Password field
	sf::Text alertText;  // Text displaying alert message
	bool isWarning = false;  // Flag indicating if a warning message should be displayed

	u32 SELECT_BUTTON;  // Currently selected button in the resume

	ResumeList resumeList;  // List of players in the resume

	Security security;  // Security object for encrypting and decrypting passwords

public: 
	Game::ResumeState state = Game::RESUME_OPTION;  // Current resume state

	/**
	 * @brief Default constructor. Initializes head to nullptr.
	 */
	Resume();

	/**
	 * @brief Destructor. Deletes all players in the resume.
	 */
	~Resume();

	void handleEvent(float deltaTime, sf::Event event, sf::Vector2i position);

	void addData(Player player, u64** board);
	
	void saveData(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordFile);

	void loadData(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordFile);

	void update(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif
