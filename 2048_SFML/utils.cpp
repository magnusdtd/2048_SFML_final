#include "utils.hpp"

// Destructor for the Stack class
Stack::~Stack()
{
    // Delete all nodes in the stack
    while (this->head != nullptr) {
        Node* temp = this->head;
        this->head = temp->next;
        delete temp;
    }
}

// Push a new node onto the stack
void Stack::push(u64* x, u32 n)
{
    // Copy state and store in stack
    u64* temp = new u64[n];
    for (u32 i = 0; i < n; i++)
        temp[i] = x[i];

    Node* newNode = new Node(temp);
    newNode->next = head;
    head = newNode;
}

// Remove the top node from the stack
void Stack::pop()
{
    if (head == nullptr)
        return;
    Node* temp = head;
    head = head->next;
    delete[] temp->data;
    temp->data = nullptr;
    delete temp;
    temp = nullptr;
}

// Return the data of the top node and remove it from the stack
u64* Stack::top()
{
    if (head == nullptr)
        return nullptr;
    Node* temp = head;
    head = head->next;
    u64* tempData = temp->data;
    delete temp;
    return tempData;
}
