#include "Loader.hpp"

// loadBestScore function implementation.
u64 Input::loadBestScore(const std::string& FileName)
{
    // Open the file in binary mode for reading.
    std::ifstream input(FileName, std::ios::binary | std::ios::in);
    u64 bestScore = 0;

    // If the file is open, read the best score from it.
    if (input.is_open()) {
        input.read(reinterpret_cast<char*>(&bestScore), sizeof(u64));
        input.close();
    }
    else
        // If the file could not be opened, print an error message.
        std::cerr << "Unable to open file: " << FileName << std::endl;

    // Return the best score.
    return bestScore;
}

// saveBestScore function implementation.
void Output::saveBestScore(const std::string& FileName, u64 score)
{
    // Open the file in binary mode for writing.
    std::ofstream output(FileName, std::ios::binary);

    // If the file is open, write the score to it.
    if (output.is_open()) {
        output.write(reinterpret_cast<const char*>(&score), sizeof(u64));
        output.close();
    }
    else
        // If the file could not be opened, print an error message.
        std::cerr << "Unable to open file: " << FileName << std::endl;
}
