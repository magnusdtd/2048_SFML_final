#include "security.hpp"

std::string Security::encrypt(std::string data) {
    if (key.empty())
        return data;

    std::string result = data;
    for (size_t i = 0; i < data.size(); i++) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

std::string Security::decrypt(const std::string& data) {
    return encrypt(data);
}
