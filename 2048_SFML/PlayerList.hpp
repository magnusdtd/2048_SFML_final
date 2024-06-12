#ifndef PLAYER_LIST_HPP
#define PLAYER_LIST_HPP

#include "SFML/Graphics.hpp"
#include "Player.hpp"
#include "security.hpp"
#include <fstream>

/**
 * @class PlayerList
 * @brief A class to manage a list of players.
 *
 * This class provides methods to add, remove, retrieve players,
 * show top 20 players, load and save player data, and reverse the player list.
 */
class PlayerList : public sf::Drawable {
	sf::Font font; ///< Font for displaying text.
	std::string key; ///< Key for encryption and decryption.

	Player* head; ///< Pointer to the first player in the list.
	u64 size; ///< Number of players in the list.
public:
	/**
	 * @brief Default constructor. Initializes head to nullptr.
	 */
	PlayerList();

	/**
	 * @brief Destructor. Deletes all players in the list.
	 */
	~PlayerList();

	/**
	 * @brief Returns the number of players in the list.
	 * @return The number of players in the list.
	 */
	u64 getSize() const {
		return size;
	}

	/**
	 * @brief Adds a player to the list.
	 * @param userName The name of the player.
	 * @param score The score of the player.
	 * @param timeToComplete The time taken by the player to complete the game.
	 */
	void addPlayer(std::string userName, u64 score, double timeToComplete, std::string password);

	/**
	 * @brief Adds a player to the list.
	 * @param A player object.
	 */
	void addPlayer(Player player);

	/**
	 * @brief Removes a player from the list.
	 * @param userName The name of the player to be removed.
	 */
	void removePlayer(std::string userName);

	/**
	 * @brief Retrieves a player from the list.
	 * @param userName The name of the player to be retrieved.
	 * @return A pointer to the player if found, nullptr otherwise.
	 */
	Player* getPlayer(std::string userName);

	/**
	* @brief Find the player have the userName.
	* @param name of the user who want to find.
	* @return true if there is a player with the same name in playerlist, otherwise return fasle.
	*/
	bool findPlayer(std::string userName);

	/**
	* @brief Find position of the player on top 20 list.
	* @param Score of player.
	* @return A position in top 20 list.
	*/
	u64 findPlayerPosition(u64 score, double time);

	/**
	* @brief Return the max score in the list.
	* @return Max score in the list.
	*/
	u64 getMaxScore();

	/**
	* @brief Write the max score to the file.
	* @param bestScoreFile The name of the file to save the max score.
	*/
	void writeMaxScore(std::string bestScoreFile);

	/**
	 * @brief Displays the top 20 players.
	 */
	void showList(sf::RenderWindow& window, u64 n);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	* @brief clear all data in the file.
	*/
	void clearDataFile(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordFile);

	/**
	 * @brief Loads player data from files.
	 * @param fileName The name of the file containing player names.
	 * @param fileScore The name of the file containing player scores.
	 * @param fileTime The name of the file containing player completion times.
	 * @param passwordFile The name of the file containing player passwords.
	 */
	void loadData(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordFile);

	/**
	 * @brief Saves player data to files.
	 * @param fileName The name of the file to save player names.
	 * @param fileScore The name of the file to save player scores.
	 * @param fileTime The name of the file to save player completion times.
	 * @param passwordFile The name of the file to save player passwords.
	 */
	void saveData(std::string nameFile, std::string scoreFile, std::string timeFile, std::string passwordFile);
};

#endif