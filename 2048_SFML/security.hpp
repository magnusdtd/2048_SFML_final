#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <string>

// The Security namespace contains functions for simple XOR cipher encryption and decryption.
namespace Security {
    /**
    * @brief Encrypts the given data using the given key with the XOR cipher.
    * The key is repeated as necessary to match the length of the data. 
    * @param data: The data to encrypt.
    * @param key: The key to use for encryption.
    * @return: The encrypted data.
    */
    std::string encrypt(std::string data, std::string key) {
        std::string result = data;
        for (size_t i = 0; i < data.size(); i++) {
            result[i] = data[i] ^ key[i % key.size()];
        }
        return result;
    }

    /**
    * @brief Decrypts the given data using the given key with the XOR cipher.
    * This function is identical to the encrypt function, because the XOR cipher
    * is symmetric - the same operation is used for both encryption and decryption.
    * @param data: The encrypted data to decrypt.
    * @param key: The key to use for decryption.
    * @return: The decrypted data.
    */
    std::string decrypt(const std::string& data, const std::string& key) {
        return encrypt(data, key);
    }
}

#endif