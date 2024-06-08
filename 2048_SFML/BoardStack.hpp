#ifndef BOARD_STACK_HPP
#define BOARD_STACK_HPP

#include "utils.hpp"

class BoardNode {
public:
    u64* data;
    BoardNode* next;

    BoardNode() {
        data = nullptr;
        next = nullptr;
    }

    BoardNode(u64* data) {
        this->data = data;
        this->next = nullptr;
    }
};


class BoardStack {
    BoardNode* head;
public:
    BoardStack() {
        head = nullptr;
    }

    ~BoardStack();

    void push(u64* data, u32 n);
    void pop();
    u64* top();


    bool empty() {
        return (head == nullptr) ? true : false;
    }
};

#endif