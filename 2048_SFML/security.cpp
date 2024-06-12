#include "security.hpp"


std::string Security::encrypt(std::string data, std::string key) {
    if (key.empty())
        return data;

    std::string result = data;
    for (size_t i = 0; i < data.size(); i++) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

std::string Security::decrypt(const std::string& data, const std::string& key) {
    return encrypt(data, key);
}
