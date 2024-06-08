#include "BoardStack.hpp"


BoardStack::~BoardStack()
{

    while (this->head != nullptr) {
        BoardNode* temp = this->head;
        this->head = temp->next;
        delete temp;
    }
}


void BoardStack::push(u64* data, u32 n)
{

    u64* temp = new u64[n];
    for (u32 i = 0; i < n; i++)
        temp[i] = data[i];

    BoardNode* newNode = new BoardNode(temp);
    newNode->next = head;
    head = newNode;
}


void BoardStack::pop()
{
    if (head == nullptr)
        return;
    BoardNode* temp = head;
    head = head->next;
    delete[] temp->data;
    temp->data = nullptr;
    delete temp;
    temp = nullptr;
}

// Return the data of the top node and remove it from the stack
u64* BoardStack::top()
{
    if (head == nullptr)
        return nullptr;
    BoardNode* temp = head;
    head = head->next;
    u64* tempData = temp->data;
    delete temp;
    return tempData;
}