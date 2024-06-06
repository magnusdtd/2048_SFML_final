#ifndef UTILS_HPP
#define UTILS_HPP
#include <random>

// Define types for easier use in the rest of the code
typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

// Node class for use in the Stack class
class Node {
public:
    u64* data; // Pointer to the data the node holds
    Node* next; // Pointer to the next node in the stack

    Node() {
        data = nullptr;
        next = nullptr;
    }

    // Constructor that initializes the node with data
    Node(u64* data) {
        this->data = data;
        this->next = nullptr;
    }
};

// Stack class for storing game states
class Stack {
    Node* head; // Pointer to the top of the stack

public:
    Stack() {
        head = nullptr;
    }

    ~Stack(); // Destructor that deletes all nodes in the stack

    void push(u64* x, u32 n); // Pushes a new node onto the stack
    void pop(); // Removes the top node from the stack
    u64* top(); // Returns the data of the top node and removes it from the stack

    // Checks if the stack is empty
    bool empty() {
        return (head == nullptr) ? true : false;
    }
};

// Function for generating random numbers
template<typename T>
inline T Random(T start, T end) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<T> dist(start, end);
    return dist(mt);
}

#endif
