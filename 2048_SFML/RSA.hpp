#ifndef RSA_HPP
#define RSA_HPP

/* Link: https://en.wikipedia.org/wiki/RSA_(cryptosystem)#Operation */

#include <iostream>
#include <cmath>
#include "Utils.hpp"

class RSA {
private:
    u64 n;
    u64 totient;
    u64 e;
    u64 d;

    u64 findE(u64 totient);

    u64 findD(u64 e, u64 totient);

    u64 gcd(u64 a, u64 b);

    u64 modExponent(u64 base, u64 exp, u64 mod);

public:
    RSA(u64 p, u64 q);

    u64 encrypt(u64 msg);

    u64 decrypt(u64 msg);

    u64* encryptString(const std::string& str);

    std::string decryptString(u64*& encrypted, u64 n);
};

#endif
