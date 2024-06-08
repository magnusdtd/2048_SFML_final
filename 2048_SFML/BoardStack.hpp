#ifndef BOARD_STACK_HPP
#define BOARD_STACK_HPP

#include "utils.hpp"
#include <iostream>

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

    void print(u32 size) {
        BoardNode* temp = head;
        int t = 1;
        std::cout << "---------------BOARD STACK-------------\n";
        while (temp != nullptr) {
            std::cout << "Board Node " << t++ << ": ";
            for (u32 i = 0; i < size * size; i++) {
                std::cout << temp->data[i] << " ";
            }
            std::cout << "\n";
            temp = temp->next;
        }
        std::cout << "---------------------------------------\n";
    }
};

#endif