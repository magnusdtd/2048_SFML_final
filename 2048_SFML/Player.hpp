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
public:
    std::string userName; ///< The player's name.
    u64 score; ///< The player's score.
    double timeToComplete; ///< The time it took the player to complete the game.

    Player* next; ///< A pointer to the next player in the list.

    /**
     * @brief Construct a new Player object.
     *
     * @param userName The player's name.
     * @param score The player's score.
     * @param timeToComplete The time it took the player to complete the game.
     */
    Player(const std::string& userName, u64 score, double timeToComplete)
        : userName(userName), score(score), timeToComplete(timeToComplete), next(nullptr) {}
};

#endif
