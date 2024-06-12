#include "utils.hpp"

std::string generateRandomString(u32 length)
{
    const std::string CHARACTERS
        = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv"
        "wxyz0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, (u32)CHARACTERS.size() - 1);

    // Generate the random string
    std::string randomString;
    for (u32 i = 0; i < length; ++i)
        randomString += CHARACTERS[distribution(generator)];

    return randomString;
}
