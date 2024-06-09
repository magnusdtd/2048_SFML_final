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
 * @brief Adds a player to the list.
 * @param userName The name of the player.
 * @param score The score of the player.
 * @param timeToComplete The time taken by the player to complete the game.
 */
void PlayerList::addPlayer(std::string userName, u64 score, double timeToComplete, std::string password)
{
	Player* newPlayer = new Player(userName, score, timeToComplete, password);

	if (head == nullptr || head->getScore() < score || (head->getScore() == score && head->getTime() > timeToComplete)) {
		newPlayer->next = head;
		head = newPlayer;
		return;
	}

	Player* temp = head, *prev = head;
	while (temp != nullptr && temp->getScore() >= score) {
		prev = temp;
		temp = temp->next;
	}

	while (temp != nullptr && temp->getScore() == score && temp->getTime() <= timeToComplete) {
		prev = temp;
		temp = temp-> next;
	}

	newPlayer->next = temp;
	prev->next = newPlayer;
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

	delete temp;
}

/**
 * @brief Displays the top 20 players.
 */
void PlayerList::showTop20()
{
	Player* temp = head;

	u32 count = 0;
	while (temp != nullptr && count < 20) {
		std::cout << "Username: ";
		for (auto c : temp->getName())
			std::cout << c;
		std::cout << "\n";
		std::cout << "Score: " << temp->getScore() << "\n";
		std::cout << "Time to complete: " << temp->getTime() << "\n";
		std::cout << "Password: ";
		for (auto c : temp->getPassword())
			std::cout << c;
		std::cout << "\n\n";


		count++;
		temp = temp->next;
	}
}

/**
* @brief Loads player data from files.
* @param fileName The name of the file containing player names.
* @param fileScore The name of the file containing player scores.
* @param fileTime The name of the file containing player completion times.
* @param passwordName The name of the file containing player passwords.
*/
void PlayerList::loadData(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordName)
{
	std::fstream inputName(nameFile, std::ios::binary | std::ios::in);
	std::fstream inputScore(scoreFile, std::ios::binary | std::ios::in);
	std::fstream inputTimeToComplete(timeFile, std::ios::binary | std::ios::in);
	std::fstream inputPassword(passwordName, std::ios::binary | std::ios::in);

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
		for (auto ch : passwordName)
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

		if (inputName.eof() || inputScore.eof() || inputTimeToComplete.eof()) 
			break;  // Check for EOF after trying to read

		/* Read score */
		inputScore.read(reinterpret_cast<char*>(&score), sizeof(u64));

		/* Read time */
		inputTimeToComplete.read(reinterpret_cast<char*>(&timeToComplete), sizeof(double));

		/* Read password */
		inputPassword.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		password.resize(size);
		inputPassword.read(&password[0], size);

		this->addPlayer(userName, score, timeToComplete, password);
	}


	inputName.close();;
	inputScore.close();
	inputTimeToComplete.close();
	inputPassword.close();
}

/**
* @brief Saves player data to files.
* @param fileName The name of the file to save player names.
* @param fileScore The name of the file to save player scores.
* @param fileTime The name of the file to save player completion times.
* @param passwordName The name of the file to save player passwords.
*/
void PlayerList::saveData(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordName)
{
	std::fstream outputName(nameFile, std::ios::binary | std::ios::out);
	std::fstream outputScore(scoreFile, std::ios::binary | std::ios::out);
	std::fstream outputTimeToComplete(timeFile, std::ios::binary | std::ios::out);
	std::fstream outputPassword(passwordName, std::ios::binary | std::ios::out);

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

	u64 score = 0;
	double timeToComplete = 0;
	size_t size = 0;

	Player *temp = head;
	while (temp != nullptr) {
		/* Name */
		size = temp->getName().size();
		outputName.write(reinterpret_cast<char*>(&size), sizeof(size_t));
		outputName.write(temp->getName().c_str(), size);

		score = temp->getScore();
		outputScore.write(reinterpret_cast<char*>(&score), sizeof(u64));

		timeToComplete = temp->getTime();
		outputTimeToComplete.write(reinterpret_cast<char*>(&timeToComplete), sizeof(double));

		/* Password */
		size = temp->getPassword().size();
		outputPassword.write(reinterpret_cast<char*>(&size), sizeof(size_t));
		outputPassword.write(temp->getPassword().c_str(), size);


		temp = temp->next;
	}

	outputName.close();
	outputScore.close();
	outputTimeToComplete.close();
	outputPassword.close();
}
