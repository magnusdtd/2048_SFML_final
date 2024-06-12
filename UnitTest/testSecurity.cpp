#include "pch.h"
#include "../2048_SFML/security.hpp"
#include "../2048_SFML/security.cpp"

class SecurityTest : public ::testing::Test {
protected:
    Security security;
};

TEST_F(SecurityTest, EncryptDecryptTest) {
    std::string original = "Hello, World!";
    std::string encrypted = security.encrypt(original);
    std::string decrypted = security.decrypt(encrypted);

    EXPECT_NE(original, encrypted);
    EXPECT_EQ(original, decrypted);
}

TEST_F(SecurityTest, EmptyStringTest) {
    std::string original = "";
    std::string encrypted = security.encrypt(original);
    std::string decrypted = security.decrypt(encrypted);

    EXPECT_EQ(original, encrypted);
    EXPECT_EQ(original, decrypted);
}

TEST_F(SecurityTest, EncryptDecryptWithSpecialCharactersTest) {
    std::string original = "Hello, World!@#$%^&*()_+{}|:\"<>?`~";
    std::string encrypted = security.encrypt(original);
    std::string decrypted = security.decrypt(encrypted);

    EXPECT_NE(original, encrypted);
    EXPECT_EQ(original, decrypted);
}