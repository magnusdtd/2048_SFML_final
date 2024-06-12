#include "pch.h"
#include "../2048_SFML/RSA.hpp"
#include "../2048_SFML/RSA.cpp"

TEST(RSATest, EncryptDecrypt) {
    RSA rsa(17, 11); // p=17, q=11
    u64 message = 88; // some random message
    u64 encrypted = rsa.encrypt(message);
    u64 decrypted = rsa.decrypt(encrypted);
    EXPECT_EQ(message, decrypted);
}

TEST(RSATest, EncryptDecryptString) {
    RSA rsa(17, 11); // p=17, q=11
    std::string message = "Hello, World!";
    u64* encrypted = rsa.encryptString(message);
    std::string decrypted = rsa.decryptString(encrypted, message.size());
    delete[] encrypted;
    EXPECT_EQ(message, decrypted);
}
