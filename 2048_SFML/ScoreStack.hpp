#ifndef SCORE_STACK_HPP
#define SCORE_STACK_HPP

#include "utils.hpp"

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
};

#endif