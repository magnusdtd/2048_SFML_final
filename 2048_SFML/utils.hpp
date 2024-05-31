#ifndef UTILS_HPP
#define UTILS_HPP

#include "random"

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

namespace Stack {
    struct Node {
        u64* data;
        Node* next;
    };
    struct Stack {
        Node* head;
    };
    static Stack redoStack;
    static Stack undoStack;

    void init(Stack& st);
    void push(Stack& st, u64* x, u32 n);
    void pop(Stack& st);
    bool isEmpty(Stack st);
    u64* top(Stack& st);
    void freeMemory(Stack& st);
}

s64 Random(s64 start, s64 end);

#endif
