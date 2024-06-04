#include "utils.hpp"

void Stack::init(Stack& st) {
    st.head = nullptr;
}

void Stack::push(Stack& st, u64* x, u32 n) {
    // Copy state and store in stack
    u64* temp = new u64[n];
    for (u32 i = 0; i < n; i++)
        temp[i] = x[i];

    Node* newNode = new Node;
    newNode->data = temp;
    newNode->next = st.head;
    st.head = newNode;
}

void Stack::pop(Stack& st) {
    if (st.head == nullptr)
        return;
    Node* temp = st.head;
    st.head = st.head->next;
    u64* tempData = temp->data;

    delete[] tempData;
    tempData = nullptr;
    delete temp;
    temp = nullptr;
}

bool Stack::isEmpty(Stack st) {
    return (st.head == nullptr) ? true : false;
}

u64* Stack::top(Stack& st) {
    if (st.head == nullptr)
        return nullptr;
    Node* temp = st.head;
    st.head = st.head->next;
    u64* tempData = temp->data;
    delete temp;
    return tempData;
}

void Stack::freeMemory(Stack& st)
{
    while (st.head != nullptr)
    {
        u64* tempData = st.head->data;
        Node* temp = st.head;
        st.head = st.head->next;

        delete[] tempData;
        tempData = nullptr;
        delete temp;
        temp = nullptr;
    }
}

