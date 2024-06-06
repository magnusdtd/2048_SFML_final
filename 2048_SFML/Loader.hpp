#ifndef LOADER_HPP
#define LOADER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "utils.hpp"

// The Input namespace is used to group input related functions.
namespace Input {
    // loadBestScore function is used to load the best score from a file.
    // @param FileName: The name of the file from which to load the best score.
    // @return The best score loaded from the file.
    u64 loadBestScore(const std::string& FileName);
}

// The Output namespace is used to group output related functions.
namespace Output {
    // saveBestScore function is used to save the best score to a file.
    // @param FileName: The name of the file to which to save the best score.
    // @param score: The score to save.
    void saveBestScore(const std::string& FileName, u64 score);
}
#endif

