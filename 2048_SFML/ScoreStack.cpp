#include "ScoreStack.hpp"

ScoreStack::ScoreStack(const ScoreStack& other)
{
	head = nullptr;
	ScoreNode* current = other.head;
	ScoreNode* last = nullptr;
	while (current != nullptr) {
		ScoreNode* newNode = new ScoreNode(current->data);

		if (last == nullptr)
			head = newNode;
		else
			last->next = newNode;
		last = newNode;

		current = current->next;
	}
}

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

void ScoreStack::clear()
{
	while (head != nullptr) {
		pop();
	}
}

void ScoreStack::writeToBinaryFile(std::string filename) {
	std::ofstream outFile(filename, std::ios::binary);
	if (!outFile.is_open()) {
		std::cerr << "Failed to open file for writing: ";
		for (auto c : filename)
			std::cerr << c;
		std::cerr << "\n";
		return;
	}

	ScoreNode* current = head;
	while (current != nullptr) {
		outFile.write(reinterpret_cast<const char*>(&current->data), sizeof(current->data));
		current = current->next;
	}

	outFile.close();
}

void ScoreStack::reverse() {
	ScoreNode* prev = nullptr;
	ScoreNode* current = head;
	ScoreNode* next = nullptr;
	while (current != nullptr) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}

void ScoreStack::readFromBinaryFile(std::string filename) {
	std::ifstream inFile(filename, std::ios::binary);
	if (!inFile.is_open()) {
		std::cerr << "Failed to open file for reading: ";
		for (auto c : filename)
			std::cerr << c;
		std::cerr << "\n";
		return;
	}

	while (!empty()) {
		pop();
	}

	u64 score = 0;
	while (inFile.read(reinterpret_cast<char*>(&score), sizeof(score)))
		push(score);

	// After reading all scores and pushing them onto the stack, reverse the stack
	reverse();

	inFile.close();
}



