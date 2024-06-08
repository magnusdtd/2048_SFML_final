#ifndef SCORE_STACK_HPP
#define SCORE_STACK_HPP

#include "utils.hpp"
#include <iostream>

class ScoreNode {
public:
    u64 data;
    ScoreNode* next;

    ScoreNode() {
        data = 0;
        next = nullptr;
    }

    ScoreNode(u64 data) {
        this->data = data;
        this->next = nullptr;
    }
};


class ScoreStack {
    ScoreNode* head;
public:
    ScoreStack() {
        head = nullptr;
    }

    ~ScoreStack();

    void push(u64 score);
    void pop();
    u64 top();


    bool empty() {
        return (head == nullptr) ? true : false;
    }

    void print() {
        std::cout << "---------------SCORE STACK-------------\n";
        int t = 1;
		ScoreNode* temp = head;
		while (temp != nullptr) {
			std::cout << "Score Node " << t++ << ": " << temp->data << "\n";
			temp = temp->next;
		}
        std::cout << "---------------------------------------\n";
	}
};

#endif