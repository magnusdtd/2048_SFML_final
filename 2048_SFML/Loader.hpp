#ifndef LOADER_HPP
#define LOADER_HPP

#include <fstream>
#include <iostream>
#include "utils.hpp"

#define DATABASE "scores.txt"
#define BESTSCORE "bestScore.txt"

namespace Input {
	u64 loadScoreAndGetMaxScore(u64 order_number);
	u64 loadBestScore();
	void saveBestScore(u64 score);
}


#endif

