#include "Loader.hpp"

u64 Input::loadBestScore(const std::string& FileName)
{
    std::ifstream input(FileName, std::ios::binary | std::ios::in);
    u64 bestScore = 0;

    if (input.is_open()) {
        input.read(reinterpret_cast<char*>(&bestScore), sizeof(u64));
        input.close();
    }
    else
        std::cerr << "Unable to open file: " << FileName << std::endl;

    return bestScore;
}

void Output::saveBestScore(const std::string& FileName, u64 score)
{
	std::ofstream output(FileName, std::ios::binary);

	if (output.is_open()) {
		output.write(reinterpret_cast<const char*>(&score), sizeof(u64));
		output.close();
	}
	else
		std::cerr << "Unable to open file: " << FileName << std::endl;
}