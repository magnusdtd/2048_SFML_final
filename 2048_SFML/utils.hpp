#ifndef UTILS_HPP
#define UTILS_HPP
#include <random>
#include <type_traits>

// Define types for easier use in the rest of the code
typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

// Function for generating random numbers
template<typename T>
inline T Random(T start, T end) {
    std::random_device rd;
    std::mt19937 mt(rd());
    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dist(start, end);
        return dist(mt);
    }
    else if constexpr (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dist(static_cast<T>(start), static_cast<T>(end));
        return dist(mt);
    }
    else {
        throw std::invalid_argument("Invalid type for template Random");
    }
}

#endif
