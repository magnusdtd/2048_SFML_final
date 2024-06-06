#ifndef LOADER_HPP
#define LOADER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "utils.hpp"

namespace Input {
	u64 loadBestScore(const std::string& FileName);
}

namespace Output {
	void saveBestScore(const std::string& FileName, u64 score);
}
#endif

