#include "utils.hpp"

Stack::~Stack()
{
	while (this->head != nullptr) {
		Node* temp = this->head;
		this->head = temp->next;
	}
}

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
