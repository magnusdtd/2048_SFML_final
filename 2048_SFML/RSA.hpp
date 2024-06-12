#ifndef RSA_HPP
#define RSA_HPP

/* Link: https://en.wikipedia.org/wiki/RSA_(cryptosystem)#Operation */

#include <iostream>
#include <cmath>
#include "Utils.hpp"

/**
 * RSA class for RSA encryption and decryption.
 */
class RSA {
private:
    u64 n; // The modulus for both the public and private keys
    u64 totient; // Euler's totient function (phi)
    u64 e; // The public exponent
    u64 d; // The private exponent

    /**
     * Function to find the public exponent 'e'.
     * @param totient - Euler's totient function (phi)
     * @return - The public exponent 'e'
     */
    u64 findE(u64 totient);

    /**
     * Function to find the private exponent 'd'.
     * @param e - The public exponent
     * @param totient - Euler's totient function (phi)
     * @return - The private exponent 'd'
     */
    u64 findD(u64 e, u64 totient);

    /**
     * Function to find the greatest common divisor of two numbers.
     * @param a - The first number
     * @param b - The second number
     * @return - The greatest common divisor of 'a' and 'b'
     */
    u64 gcd(u64 a, u64 b);

    /**
     * Function to calculate the modular exponentiation.
     * @param base - The base number
     * @param exp - The exponent
     * @param mod - The modulus
     * @return - The result of the modular exponentiation
     */
    u64 modExponent(u64 base, u64 exp, u64 mod);

public:

    /**
    * Default constructor for the RSA class.
    */
    RSA() : n(0), totient(0), e(0), d(0) {}

    /**
     * Constructor for the RSA class.
     * @param p - The first prime number
     * @param q - The second prime number
     */
    RSA(u64 p, u64 q);

    /**
     * Function to encrypt a message.
     * @param msg - The message to encrypt
     * @return - The encrypted message
     */
    u64 encrypt(u64 msg);

    /**
     * Function to decrypt a message.
     * @param msg - The encrypted message
     * @return - The decrypted message
     */
    u64 decrypt(u64 msg);

    /**
     * Function to encrypt a string.
     * @param str - The string to encrypt
     * @return - The encrypted string
     */
    u64* encryptString(const std::string& str);

    /**
     * Function to decrypt a string.
     * @param encrypted - The encrypted string
     * @param n - The size of the encrypted string
     * @return - The decrypted string
     */
    std::string decryptString(u64*& encrypted, u64 n);
};

#endif
