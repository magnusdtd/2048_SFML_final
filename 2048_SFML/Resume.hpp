#ifndef RESUME_HPP
#define RESUME_HPP

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "PlayerList.hpp"
#include "TextField.hpp"
#include "layout.hpp"
#include "ResumeData.hpp"
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

	/* RESUME_REGISTER and RESUME_CONTINUE */
	sf::Text account1;  // Text displaying the first account
	sf::Text account2;  // Text displaying the second account
	sf::Text account3;  // Text displaying the third account
	sf::Text account4;  // Text displaying the fourth account
	sf::Text account5;  // Text displaying the fifth account

	/* RESUME_OPTION */
	sf::Text resumeOption1;  // Text displaying the resume option1
	sf::Text resumeOption2;  // Text displaying the resume option2

	/* RESUME_CONTINUE */
	sf::Texture backgroundTextureResumeContinueLogin;  // Texture for resume background
	sf::Sprite backgroundResumeContinueLogin;  // Sprite for resume background

	TextField usernameField;  // Username field
	TextField passwordField;  // Password field
	sf::Text alertText;
	bool isWarning = false;

	u32 SELECT_BUTTON;  // Currently selected button in the resume

	ResumeData* head;  // Head of the resume list
	Player currentPlayer;  // Current player
	u64** boardData;  // Board data

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


	/**
	* @brief Returns the current players in the resume.
	*/
	Player getPlayer() { return currentPlayer; }

	u64** getBoardData() { return boardData; }

	void update(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif
