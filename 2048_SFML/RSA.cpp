#include "RSA.hpp"

/**
 * Function to find the public exponent 'e'.
 * @param totient - Euler's totient function (phi)
 * @return - The public exponent 'e'
 */
u64 RSA::findE(u64 totient)
{
    u64 e = 3;
    while (gcd(e, totient) != 1) {
        e += 2;
    }
    return e;
}

/**
 * Function to find the private exponent 'd'.
 * @param e - The public exponent
 * @param totient - Euler's totient function (phi)
 * @return - The private exponent 'd'
 */
u64 RSA::findD(u64 e, u64 totient)
{
    u64 m0 = totient, t, q;
    u64 x0 = 0, x1 = 1;

    if (totient == 1)
        return 0;

    while (e > 1)
    {
        q = e / totient;

        t = totient;

        totient = e % totient, e = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

/**
 * Function to find the greatest common divisor of two numbers.
 * @param a - The first number
 * @param b - The second number
 * @return - The greatest common divisor of 'a' and 'b'
 */
u64 RSA::gcd(u64 a, u64 b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

/**
 * Function to calculate the modular exponentiation.
 * @param base - The base number
 * @param exp - The exponent
 * @param mod - The modulus
 * @return - The result of the modular exponentiation
 */
u64 RSA::modExponent(u64 base, u64 exp, u64 mod)
{
    u64 res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return res;
}

/**
 * Constructor for the RSA class.
 * @param p - The first prime number
 * @param q - The second prime number
 */
RSA::RSA(u64 p, u64 q)
{
    n = p * q;
    totient = (p - 1) * (q - 1);
    e = findE(totient);
    d = findD(e, totient);
}

/**
 * Function to encrypt a message.
 * @param msg - The message to encrypt
 * @return - The encrypted message
 */
u64 RSA::encrypt(u64 msg)
{
    return modExponent(msg, e, n);
}

/**
 * Function to decrypt a message.
 * @param msg - The encrypted message
 * @return - The decrypted message
 */
u64 RSA::decrypt(u64 msg)
{
    return modExponent(msg, d, n);
}

/**
 * Function to encrypt a string.
 * @param str - The string to encrypt
 * @return - The encrypted string
 */
u64* RSA::encryptString(const std::string& str)
{
    u64* encrypted = new u64[str.size()];
    for (u32 i = 0; i < str.size(); i++) {
        u64 encryptedChar = encrypt(str[i]);
        //if (encryptedChar > std::numeric_limits<char>::max()) {
        //    // Handle the error, e.g., throw an exception
        //    throw std::runtime_error("Encryption overflow");
        //}
        encrypted[i] = encryptedChar;
    }
    return encrypted;
}

/**
 * Function to decrypt a string.
 * @param encrypted - The encrypted string
 * @param n - The size of the encrypted string
 * @return - The decrypted string
 */
std::string RSA::decryptString(u64*& encrypted, u64 n)
{
    std::string decrypted;
    for (u64 i = 0; i < n; i++)
        decrypted.push_back(static_cast<char>(decrypt(encrypted[i])));
    return decrypted;
}
