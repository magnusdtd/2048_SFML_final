#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <string>

namespace Security {
    static std::string encrypt(std::string data, std::string key);
    static std::string decrypt(const std::string& data, const std::string& key);
}

#endif