#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <string>

namespace Security {
    std::string encrypt(std::string data, std::string key);
    std::string decrypt(const std::string& data, const std::string& key);
}

#endif