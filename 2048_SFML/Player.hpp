#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include "utils.hpp"

/**
 * @class Player
 * @brief A class to represent a player in the game.
 *
 * This class contains the player's name, score, and time to complete the game.
 * It also contains a pointer to the next player, for use in a linked list of players.
 */
class Player {
private: // User's information can not be accessed directly
    std::string userName; ///< The player's name.
    u64 score; ///< The player's score.
    double timeToComplete; ///< The time it took the player to complete the game.
    std::string password; ///< The player's password.
public:
    Player* next; ///< A pointer to the next player in the list.

    /**
    * @brief Default construct a new Player object.
    */
    Player() : userName(""), score(0), timeToComplete(0), password(""), next(nullptr) {}

    /**
     * @brief Construct a new Player object.
     * @param userName The player's name.
     * @param score The player's score.
     * @param timeToComplete The time it took the player to complete the game.
     * @param password The player's password.
     */
    Player(const std::string& userName, u64 score, double timeToComplete, std::string password)
        : userName(userName), score(score), timeToComplete(timeToComplete),
        password(password), next(nullptr) {}

    /**
    * @brief Set the player's name.
	 * @param userName The player's name.
	 */
    void setUserName(const std::string& userName) { this->userName = userName; }

    /**
	 * @brief Set the player's score.
	 * @param score The player's score.
	 */
    void setScore(u64 score) { this->score = score; }

    /**
    * @brief Set the time it took the player to complete the game.
    */
    void setTime(double timeToComplete) { this->timeToComplete = timeToComplete; }

    /**
    * @brief Set the player's password.
    */
    void setPassword(const std::string& password) { this->password = password; }
    
    /**
     * @brief Get the player's name.
     * @return The player's name.
     */
    std::string getName() const { return userName; }

    /**
     * @brief Get the player's score.
     * @return The player's score.
     */
    u64 getScore() const { return score; }

    /**
     * @brief Get the time it took the player to complete the game.
     * @return The time it took the player to complete the game.
     */
    double getTime() const { return timeToComplete; }

    /**
     * @brief Get the player's password.
     * @return The player's password.
     */
    std::string getPassword() const { return password; }
};

#endif
