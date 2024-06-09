#include "RSA.hpp"

u64 RSA::findE(u64 totient)
{
    u64 e = 3;
    while (gcd(e, totient) != 1) {
        e += 2;
    }
    return e;
}

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

u64 RSA::gcd(u64 a, u64 b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

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

RSA::RSA(u64 p, u64 q)
{
    n = p * q;
    totient = (p - 1) * (q - 1);
    e = findE(totient);
    d = findD(e, totient);
}

u64 RSA::encrypt(u64 msg)
{
    return modExponent(msg, e, n);
}

u64 RSA::decrypt(u64 msg)
{
    return modExponent(msg, d, n);
}

u64* RSA::encryptString(const std::string& str)
{
    u64* encrypted = new u64[str.size()];
    for (u32 i = 0; i < str.size(); i++)
        encrypted[i] = encrypt(str[i]);
    return encrypted;
}

std::string RSA::decryptString(u64*& encrypted, u64 n)
{
    std::string decrypted;
    for (u64 i = 0; i < n; i++)
        decrypted.push_back(static_cast<char>(decrypt(encrypted[i])));
    return decrypted;
}
