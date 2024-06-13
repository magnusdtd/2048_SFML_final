#include "BoardStack.hpp"

BoardStack::~BoardStack()
{
    while (this->head != nullptr) {
        BoardNode* temp = this->head;
        this->head = temp->next;
        delete[] temp->data;
        delete temp;
    }
    std::cout << "BoardStack destroyed\n";
}

BoardStack::BoardStack(const BoardStack& other)
{
    head = nullptr;
    BoardNode* current = other.head;
    BoardNode* last = nullptr;
    while (current != nullptr) {
        u64* dataCopy = new u64[current->dataSize];
        for (u32 i = 0; i < current->dataSize; i++) {
            dataCopy[i] = current->data[i];
        }
        BoardNode* newNode = new BoardNode(dataCopy, current->dataSize);

        if (last == nullptr)
            head = newNode;
        else
            last->next = newNode;
        last = newNode;

        current = current->next;
    }
}

void BoardStack::push(u64* data, u32 n)
{
    u64* temp = new u64[n];
    for (u32 i = 0; i < n; i++)
        temp[i] = data[i];

    BoardNode* newNode = new BoardNode(temp, n);
    newNode->next = head;
    head = newNode;
}

void BoardStack::pop()
{
    if (head == nullptr)
        return;
    BoardNode* temp = head;
    head = head->next;
    if (temp->data != nullptr) {
        delete[] temp->data;
        temp->data = nullptr;
    }
    delete temp;
}

u64* BoardStack::top()
{
    if (head == nullptr)
        return nullptr;
    return head->data;
}

void BoardStack::clear()
{
    while (head != nullptr)
		pop();
}

void BoardStack::writeToBinaryFile(const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: ";
        for (auto c : filename)
			std::cerr << c;
            std::cout << "\n";
        return;
    }

    BoardNode* current = head;
    while (current != nullptr) {
        outFile.write(reinterpret_cast<const char*>(&current->dataSize), sizeof(current->dataSize));
        outFile.write(reinterpret_cast<const char*>(current->data), current->dataSize * sizeof(u64));
        current = current->next;
    }

    outFile.close();
}

void BoardStack::reverse() {
    BoardNode* prev = nullptr;
    BoardNode* current = head;
    BoardNode* next = nullptr;
    while (current != nullptr) {
        next = current->next; // Store next
        current->next = prev; // Reverse current node's pointer
        prev = current; // Move pointers one position ahead
        current = next;
    }
    head = prev;
}

void BoardStack::readFromBinaryFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file for reading: ";
        for (auto c : filename)
            std::cerr << c;
        std::cerr << "\n";
        return;
    }

    while (!empty())
        pop();

    u32 dataSize = 0;
    u64* data;

    while (inFile.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize))) {
        data = new u64[dataSize];
        inFile.read(reinterpret_cast<char*>(data), dataSize * sizeof(u64));
        push(data, dataSize);
        // It's important not to delete[] data here; push makes a copy.
    }

    // After reading all boards and pushing them onto the stack, reverse the stack
    reverse();

    inFile.close();
}
