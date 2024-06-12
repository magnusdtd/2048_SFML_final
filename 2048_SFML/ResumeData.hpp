#ifndef RESUME_DATA_HPP
#define RESUME_DATA_HPP


#include "Player.hpp"

/**
 * @class ResumeData
 * @brief A class to manage the data of the resume state.
 *
 * This class provides methods to add, remove, retrieve players,
 * and save and load player data.
 */
class ResumeData {
	Player player;
	u64 *board;
public:
	ResumeData *next;
	ResumeData() : next(nullptr), board(nullptr) {}
	ResumeData(Player player, u64* board) : player(player), board(board), next(nullptr) {}
	~ResumeData() {
		if (board != nullptr)
			return;
		delete[] board;
	}
	Player getPlayer() const {
		return player;
	}
	u64* getBoard() const {
		return board;
	}
};

#endif