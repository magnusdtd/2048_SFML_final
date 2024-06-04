#ifndef UTILS_HPP
#define UTILS_HPP
#include <random>

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

class Node {
public:
    u64* data;
	Node* next;
    Node() {
		data = nullptr;
		next = nullptr;
	}
    Node(u64* data) {
        this->data = data;
		this->next = nullptr;
    }
};

class Stack {
	Node* head;
	/*This can help to avoid manual deletion of memory and prevent memory leaks.*/
public:
    Stack() {
		head = nullptr;
	}
	~Stack();
	void push(u64* x, u32 n);
	void pop();
	u64* top();
	bool empty() {
		return (head == nullptr) ? true : false;
	}
};

template<typename T>
inline T Random(T start, T end) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<T> dist(start, end);
    return dist(mt);
}


#endif

