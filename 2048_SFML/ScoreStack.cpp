#include "ScoreStack.hpp"

ScoreStack::~ScoreStack()
{
	while (this->head != nullptr) {
		ScoreNode* temp = this->head;
		this->head = temp->next;
		delete temp;
	}
}

void ScoreStack::push(u64 score)
{
	ScoreNode* newNode = new ScoreNode(score);
	newNode->next = head;
	head = newNode;
}

void ScoreStack::pop()
{
	if (head == nullptr)
		return;
	ScoreNode* temp = head;
	head = head->next;
	delete temp;
	temp = nullptr;
}

u64 ScoreStack::top()
{
	if (head == nullptr)
		return 0;
	return head->data;
}
