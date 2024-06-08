#include "PlayerList.hpp"

/**
 * @brief Retrieves a player from the list.
 * @param userName The name of the player to be retrieved.
 * @return A pointer to the player if found, nullptr otherwise.
 */
Player* PlayerList::getPlayer(std::string userName)
{
	Player* temp = head;

	while (temp != nullptr && temp->userName != userName)
		temp = temp->next;

	return temp;
}

/**
 * @brief Adds a player to the list.
 * @param userName The name of the player.
 * @param score The score of the player.
 * @param timeToComplete The time taken by the player to complete the game.
 */
void PlayerList::addPlayer(std::string userName, u64 score, double timeToComplete)
{
	Player* newPlayer = new Player(userName, score, timeToComplete);

	if (head == nullptr || head->score < score || (head->score == score && head->timeToComplete > timeToComplete)) {
		newPlayer->next = head;
		head = newPlayer;
		return;
	}

	Player* temp = head, *prev = head;
	while (temp != nullptr && temp->score >= score) {
		prev = temp;
		temp = temp->next;
	}

	while (temp != nullptr && temp->score == score && temp->timeToComplete <= timeToComplete) {
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

	while (temp != nullptr && temp->userName != userName) {
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
		for (auto c : temp->userName)
			std::cout << c;
		std::cout << std::endl;
		std::cout << "Score: " << temp->score << std::endl;
		std::cout << "Time to complete: " << temp->timeToComplete << std::endl;
		std::cout << std::endl;


		count++;
		temp = temp->next;
	}
}

/**
 * @brief Loads player data from files.
 * @param fileName The name of the file containing player names.
 * @param fileScore The name of the file containing player scores.
 * @param fileTime The name of the file containing player completion times.
 */
void PlayerList::loadData(std::string fileName, std::string fileScore, std::string fileTime)
{
	std::fstream inputName(fileName, std::ios::binary | std::ios::in);
	std::fstream inputScore(fileScore, std::ios::binary | std::ios::in);
	std::fstream inputTimeToComplete(fileTime, std::ios::binary | std::ios::in);

	if (!inputName.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : fileName)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!inputScore.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : fileScore)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!inputTimeToComplete.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : fileTime)
			std::cout << ch;
		std::cout << "\n";
		return;
	}

	std::string userName;
	u64 score = 0;
	double timeToComplete = 0;

	while (true) {
		// Read the string size
		size_t size = 0;
		inputName.read(reinterpret_cast<char*>(&size), sizeof(size_t));

		if (inputName.eof() || inputScore.eof() || inputTimeToComplete.eof()) 
			break;  // Check for EOF after trying to read
		
		// Resize the string to the correct size
		userName.resize(size);

		// Read the string characters
		inputName.read(&userName[0], size);

		inputScore.read(reinterpret_cast<char*>(&score), sizeof(u64));
		inputTimeToComplete.read(reinterpret_cast<char*>(&timeToComplete), sizeof(double));
		this->addPlayer(userName, score, timeToComplete);
	}


	inputName.close();;
	inputScore.close();
	inputTimeToComplete.close();
}

/**
 * @brief Saves player data to files.
 * @param fileName The name of the file to save player names.
 * @param fileScore The name of the file to save player scores.
 * @param fileTime The name of the file to save player completion times.
 */
void PlayerList::saveData(std::string fileName, std::string fileScore, std::string fileTime)
{
	std::fstream outputName(fileName, std::ios::binary | std::ios::out);
	std::fstream outputScore(fileScore, std::ios::binary | std::ios::out);
	std::fstream outputTimeToComplete(fileTime, std::ios::binary | std::ios::out);

	if (!outputName.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : fileName)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!outputScore.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : fileScore)
			std::cout << ch;
		std::cout << "\n";
		return;
	}
	if (!outputTimeToComplete.is_open()) {
		std::cerr << "Error opening file ";
		for (auto ch : fileTime)
			std::cout << ch;
		std::cout << "\n";
		return;
	}

	std::string userName;
	u64 score = 0;
	double timeToComplete = 0;

	std::cout << "Saving data...\n";
	Player *temp = head;
	while (temp != nullptr) {
		// Write the string size
		size_t size = temp->userName.size();
		outputName.write(reinterpret_cast<char*>(&size), sizeof(size_t));

		// Write the string characters
		outputName.write(temp->userName.c_str(), size);

		outputScore.write(reinterpret_cast<char*>(&temp->score), sizeof(u64));
		outputTimeToComplete.write(reinterpret_cast<char*>(&temp->timeToComplete), sizeof(double));

		temp = temp->next;
	}

	std::cout << "Data saved successfully.\n";

	outputName.close();
	outputScore.close();
	outputTimeToComplete.close();
}
