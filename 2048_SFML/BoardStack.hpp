#ifndef BOARD_STACK_HPP
#define BOARD_STACK_HPP

#include "utils.hpp"
#include <iostream>
#include <fstream>

class BoardNode {
public:
    u64* data;
    BoardNode* next;
    u32 dataSize;

    BoardNode() {
        data = nullptr;
        dataSize = 0;
        next = nullptr;
    }

    BoardNode(u64* data, u32 dataSize) {
        this->data = data;
        this->dataSize = dataSize;
        this->next = nullptr;
    }

    u32 getDataSize() const {
		return dataSize;
	}
};


class BoardStack {
    BoardNode* head;
public:
    BoardStack() : head(nullptr) {}

    ~BoardStack();

    BoardStack(const BoardStack& other);

    void push(u64* data, u32 n);

    void pop();

    u64* top();

    void clear();

    u32 getSizeOfBoard() const {
		return head->getDataSize();
	}

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

    void writeToBinaryFile(const std::string& filename);

    void readFromBinaryFile(const std::string& filename);

    void reverse();

};

#endif