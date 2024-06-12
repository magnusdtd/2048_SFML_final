#include "pch.h"
#include "../2048_SFML/security.hpp"
#include "../2048_SFML/security.cpp"

TEST(SecurityTest, EncryptDecrypt) {
    std::string data = "Hello, World!";
    std::string key = "secret";

    std::string encrypted = Security::encrypt(data, key);
    std::string decrypted = Security::decrypt(encrypted, key);

    EXPECT_NE(data, encrypted);
    EXPECT_EQ(data, decrypted);
}

TEST(SecurityTest, EncryptEmptyData) {
    std::string data = "";
    std::string key = "secret";

    std::string encrypted = Security::encrypt(data, key);
    EXPECT_EQ(data, encrypted);
}

TEST(SecurityTest, DecryptEmptyData) {
    std::string data = "";
    std::string key = "secret";

    std::string decrypted = Security::decrypt(data, key);
    EXPECT_EQ(data, decrypted);
}

TEST(SecurityTest, EncryptDecryptWithEmptyKey) {
    std::string data = "Hello, World!";
    std::string key = "";

    std::string encrypted = Security::encrypt(data, key);
    std::string decrypted = Security::decrypt(encrypted, key);

    EXPECT_EQ(data, encrypted);
    EXPECT_EQ(data, decrypted);
}

TEST(SecurityTest, EncryptDecryptForNumber) {
    std::string data = "123456789";
    std::string key = "secret";

    std::string encrypted = Security::encrypt(data, key);
    std::string decrypted = Security::decrypt(encrypted, key);

    EXPECT_NE(data, encrypted);
    EXPECT_EQ(data, decrypted);
}