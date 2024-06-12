#include "PlayerList.hpp"

/**
 * @brief Retrieves a player from the list.
 * @param userName The name of the player to be retrieved.
 * @return A pointer to the player if found, nullptr otherwise.
 */
Player* PlayerList::getPlayer(std::string userName)
{
	Player* temp = head;

	while (temp != nullptr && temp->getName() != userName)
		temp = temp->next;

	return temp;
}

/**
 * @brief Default constructor. Initializes head to nullptr.
 */
PlayerList::PlayerList() : head(nullptr), size(0) {
	if (!font.loadFromFile("Fonts/arial.ttf"))
		std::cout << "Could not load font\n";
	key = generateRandomString(16);
}

/**
 * @brief Destructor. Deletes all players in the list.
 */
PlayerList::~PlayerList()
{
	while (head != nullptr) {
		Player* temp = head;
		head = temp->next;
		delete temp;
	}
	size--;
}

/**
 * @brief Adds a player to the list.
 * @param userName The name of the player.
 * @param score The score of the player.
 * @param timeToComplete The time taken by the player to complete the game.
 */
void PlayerList::addPlayer(std::string userName, u64 score, double timeToComplete, std::string password)
{
	Player* existingPlayer = getPlayer(userName);
	if (existingPlayer != nullptr) {
		// If a player with the same name already exists and has a higher score or the same score but a lower time, don't add the new player
		if (existingPlayer->getScore() > score || (existingPlayer->getScore() == score && existingPlayer->getTime() <= timeToComplete)) {
			return;
		}
		// If a player with the same name already exists and has a lower score or the same score but a higher time, remove the existing player
		else {
			removePlayer(userName);
		}
	}

	Player* newPlayer = new Player(userName, score, timeToComplete, password);

	if (head == nullptr || head->getScore() < score || (head->getScore() == score && head->getTime() > timeToComplete)) {
		newPlayer->next = head;
		head = newPlayer;
		size++;
	}
	else {
		Player* temp = head, * prev = head;
		while (temp != nullptr && temp->getScore() >= score) {
			prev = temp;
			temp = temp->next;
		}

		while (temp != nullptr && temp->getScore() == score && temp->getTime() <= timeToComplete) {
			prev = temp;
			temp = temp->next;
		}

		newPlayer->next = temp;
		prev->next = newPlayer;

		size++;
	}

	// If the size of the list is more than 20, remove the player with the lowest score
	if (size > 20) {
		Player* temp = head, * prev = nullptr;
		while (temp->next != nullptr) {
			prev = temp;
			temp = temp->next;
		}

		if (prev == nullptr) {
			// The player to be removed is the head of the list
			head = temp->next;
		}
		else {
			prev->next = nullptr;
		}
		delete temp;
		size--;
	}
}

/**
 * @brief Adds a player to the list.
 * @param A player object.
 */
void PlayerList::addPlayer(Player player)
{
	Player* existingPlayer = getPlayer(player.getName());
	if (existingPlayer != nullptr) {
		// If a player with the same name already exists and has a higher score or the same score but a lower time, don't add the new player
		if (existingPlayer->getScore() > player.getScore() || (existingPlayer->getScore() == player.getScore() && existingPlayer->getTime() <= player.getTime())) {
			return;
		}
		// If a player with the same name already exists and has a lower score or the same score but a higher time, remove the existing player
		else {
			removePlayer(player.getName());
		}
	}

	Player* newPlayer = new Player(player); // Create a new Player object on the heap

	if (head == nullptr || head->getScore() < newPlayer->getScore() || (head->getScore() == newPlayer->getScore() && head->getTime() > newPlayer->getTime())) {
		newPlayer->next = head;
		head = newPlayer;
		size++;
	}
	else {
		Player* temp = head, * prev = head;
		while (temp != nullptr && temp->getScore() >= newPlayer->getScore()) {
			prev = temp;
			temp = temp->next;
		}

		while (temp != nullptr && temp->getScore() == newPlayer->getScore() && temp->getTime() <= newPlayer->getTime()) {
			prev = temp;
			temp = temp->next;
		}

		newPlayer->next = temp;
		prev->next = newPlayer;

		size++;
	}

	// If the size of the list is more than 20, remove the player with the lowest score
	if (size > 20) {
		Player* temp = head, * prev = nullptr;
		while (temp->next != nullptr) {
			prev = temp;
			temp = temp->next;
		}

		if (prev == nullptr) {
			// The player to be removed is the head of the list
			head = temp->next;
		}
		else {
			prev->next = nullptr;
		}
		delete temp;
		size--;
	}
}

/**
 * @brief Removes a player from the list.
 * @param userName The name of the player to be removed.
 */
void PlayerList::removePlayer(std::string userName)
{
	Player* temp = head;
	Player* prev = nullptr;

	while (temp != nullptr && temp->getName() != userName) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == nullptr)
		return;

	if (prev == nullptr)
		head = temp->next;
	else
		prev->next = temp->next;

	size--;
	delete temp;
}

/**
 * @brief Find the player have the userName.
 * @param name of the user who want to find.
 * @return true if there is a player with the same name in playerlist, otherwise return fasle.
 */
bool PlayerList::findPlayer(std::string userName)
{
	Player* temp = head;

	while (temp != nullptr) {
		if (temp->getName() == userName)
			return true;
		temp = temp->next;
	}

	return false;
}

/**
 * @brief Find position of the player on top 20 list.
 * @param Score of player.
 * @return A position in top 20 list.
 */
u64 PlayerList::findPlayerPosition(u64 score, double time)
{
	Player* temp = head;
	u64 index = 1;

	while (temp != nullptr && index <= 20) {
		if (score > temp->getScore() || (score == temp->getScore() && time < temp->getTime()))
			return index - 1;
		temp = temp->next;
		index++;
	}

	return size + 1;
}

/**
 * @brief Returns the size of the list.
 * @return The size of the list.
 */
u64 PlayerList::getMaxScore()
{
	if (head == nullptr)
		return 0;
	else
		return head->getScore();
}

/**
 * @brief Writes the maximum score to a file.
 * @param bestScoreFile The name of the file to write the maximum score to.
 */
void PlayerList::writeMaxScore(std::string bestScoreFile)
{
	std::ofstream output(bestScoreFile, std::ios::binary | std::ios::out);
	if (!output.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : bestScoreFile)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	std::string maxScoreStr = std::to_string(this->getMaxScore());
	maxScoreStr = Security::encrypt(maxScoreStr, key);
	output.write(maxScoreStr.c_str(), maxScoreStr.size());

	output.close();
}

/**
 * @brief Displays the top 20 players.
 */
void PlayerList::showList(sf::RenderWindow& window, u64 n)
{
	
}

void PlayerList::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Player* temp = head;

	u32 count = 0;
	float x = 350.0f; // Starting x position for the text
	float y = 220.0f; // Starting y position for the text
	while (temp != nullptr && count < size) {
		std::string info = std::to_string(count + 1) + ". Username: " + temp->getName() + "\n"
			+ "Score: " + std::to_string(temp->getScore()) + "\n"
			+ "Time to complete: " + std::to_string(temp->getTime()) + "\n";

		sf::Text text(info, font);
		text.setCharacterSize(24); // Set the size of the text
		text.setFillColor(sf::Color::Black); // Set the color of the text
		text.setPosition(x, y); // Set the position of the text

		target.draw(text, states); // Draw the text to the window

		y += 120.0f; // Move the y position for the next player
		count++;
		temp = temp->next;
	}
}

/**
* @brief clear all data in the file.
*/
void PlayerList::clearDataFile(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordFile)
{
	std::ofstream outputName(nameFile, std::ios::trunc);
	std::ofstream outputScore(scoreFile, std::ios::trunc);
	std::ofstream outputTimeToComplete(timeFile, std::ios::trunc);
	std::ofstream outputPassword(passwordFile, std::ios::trunc);
}

/**
* @brief Loads player data from files.
* @param fileName The name of the file containing player names.
* @param fileScore The name of the file containing player scores.
* @param fileTime The name of the file containing player completion times.
* @param passwordFile The name of the file containing player passwords.
*/
void PlayerList::loadData(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordFile)
{
	std::fstream inputName(nameFile, std::ios::binary | std::ios::in);
	std::fstream inputScore(scoreFile, std::ios::binary | std::ios::in);
	std::fstream inputTimeToComplete(timeFile, std::ios::binary | std::ios::in);
	std::fstream inputPassword(passwordFile, std::ios::binary | std::ios::in);

	if (!inputName.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : nameFile)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!inputScore.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : scoreFile)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!inputTimeToComplete.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : timeFile)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!inputPassword.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : passwordFile)
			std::cout << ch;
		std::cout << "\n";
		return;
	}

	std::string userName;
	u64 score = 0;
	double timeToComplete = 0;
	std::string password;
	size_t size = 0;

	while (true) {
		/* Read name */
		size = 0;
		inputName.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		userName.resize(size);
		inputName.read(&userName[0], size);
		userName = Security::decrypt(userName, key);

		if (inputName.eof() || inputScore.eof() || inputTimeToComplete.eof())
			break;  // Check for EOF after trying to read

		/* Read score */
		std::string encryptedScore;
		inputScore.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		encryptedScore.resize(size);
		inputScore.read(&encryptedScore[0], size);
		score = std::stoull(Security::decrypt(encryptedScore, key));

		/* Read time */
		std::string encryptedTime;
		inputTimeToComplete.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		encryptedTime.resize(size);
		inputTimeToComplete.read(&encryptedTime[0], size);
		timeToComplete = std::stod(Security::decrypt(encryptedTime, key));

		/* Read password */
		inputPassword.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		password.resize(size);
		inputPassword.read(&password[0], size);
		password = Security::decrypt(password, key);

		this->addPlayer(userName, score, timeToComplete, password);
	}

	inputName.close();
	inputScore.close();
	inputTimeToComplete.close();
	inputPassword.close();
}


/**
* @brief Saves player data to files.
* @param fileName The name of the file to save player names.
* @param fileScore The name of the file to save player scores.
* @param fileTime The name of the file to save player completion times.
* @param passwordFile The name of the file to save player passwords.
*/
void PlayerList::saveData(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordFile)
{
	std::fstream outputName(nameFile, std::ios::binary | std::ios::out);
	std::fstream outputScore(scoreFile, std::ios::binary | std::ios::out);
	std::fstream outputTimeToComplete(timeFile, std::ios::binary | std::ios::out);
	std::fstream outputPassword(passwordFile, std::ios::binary | std::ios::out);

	if (!outputName.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : nameFile)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!outputScore.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : scoreFile)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!outputTimeToComplete.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : timeFile)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!outputPassword.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : passwordFile)
			std::cout << ch;
		std::cout << "\n";
		return;
	}

	Player* temp = head;
	while (temp != nullptr) {
		/* Name */
		std::string encryptedName = Security::encrypt(temp->getName(), key);
		size_t size = encryptedName.size();
		outputName.write(reinterpret_cast<char*>(&size), sizeof(size_t));
		outputName.write(encryptedName.c_str(), size);

		/* Score */
		std::string encryptedScore = Security::encrypt(std::to_string(temp->getScore()), key);
		size = encryptedScore.size();
		outputScore.write(reinterpret_cast<char*>(&size), sizeof(size_t));
		outputScore.write(encryptedScore.c_str(), size);

		/* Time */
		std::string encryptedTime = Security::encrypt(std::to_string(temp->getTime()), key);
		size = encryptedTime.size();
		outputTimeToComplete.write(reinterpret_cast<char*>(&size), sizeof(size_t));
		outputTimeToComplete.write(encryptedTime.c_str(), size);

		/* Password */
		std::string encryptedPassword = Security::encrypt(temp->getPassword(), key);
		size = encryptedPassword.size();
		outputPassword.write(reinterpret_cast<char*>(&size), sizeof(size_t));
		outputPassword.write(encryptedPassword.c_str(), size);

		temp = temp->next;
	}

	outputName.close();
	outputScore.close();
	outputTimeToComplete.close();
	outputPassword.close();
}

