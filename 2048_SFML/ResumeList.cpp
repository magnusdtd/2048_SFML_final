#include "ResumeList.hpp"

ResumeList::~ResumeList()
{
    ResumeNode* current = head;
    while (current != nullptr) {
        ResumeNode* next = current->next;
        delete current; // BoardStack and ScoreStack destructors will be called here
        current = next;
    }
}

void ResumeList::addData(Player player, BoardStack boardStack, ScoreStack scoreStack)
{
    // Check if the list already has 5 nodes
    if (size >= 5)
        return;
 

    ResumeNode* newNode = new ResumeNode();
    newNode->player = player;
    newNode->boardStack = boardStack;
    newNode->scoreStack = scoreStack;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        ResumeNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

void ResumeList::removeData(u32 index)
{
    if (index >= size || head == nullptr) 
        return;

    ResumeNode* toDelete = head;
    if (index == 0)
        head = head->next;
    else {
        ResumeNode* current = head;
        for (u32 i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
    }

    delete toDelete;
    size--;
}

ResumeNode* ResumeList::getData(u32 index)
{
    if (index >= size) 
        return nullptr;

    ResumeNode* current = head;
    for (u32 i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}

u32 ResumeList::getSize() const
{
	return size;
}


void ResumeList::writeToFiles(const std::string& nameFile, const std::string& scoreFile, const std::string& passwordFile, const std::string& boardStackFile, const std::string& scoreStackFile) {
    std::ofstream nameOut(nameFile, std::ios::binary);
    std::ofstream scoreOut(scoreFile, std::ios::binary);
    std::ofstream passwordOut(passwordFile, std::ios::binary);
    std::ofstream boardStackOut(boardStackFile, std::ios::binary);
    std::ofstream scoreStackOut(scoreStackFile, std::ios::binary);

    ResumeNode* current = head;
    while (current != nullptr) {
        // Write player name
        size_t nameLength = current->player.getName().length();
        nameOut.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        nameOut.write(current->player.getName().c_str(), nameLength);

        // Write player score
        u64 score = current->player.getScore();
        scoreOut.write(reinterpret_cast<const char*>(&score), sizeof(score));

        // Write player password
        size_t passwordLength = current->player.getPassword().length();
        passwordOut.write(reinterpret_cast<const char*>(&passwordLength), sizeof(passwordLength));
        passwordOut.write(current->player.getPassword().c_str(), passwordLength);

        // Write BoardStack and ScoreStack data
        current->boardStack.writeToBinaryFile(boardStackFile);
        current->scoreStack.writeToBinaryFile(scoreStackFile);

        current = current->next;
    }

    nameOut.close();
    scoreOut.close();
    passwordOut.close();
    boardStackOut.close();
    scoreStackOut.close();
}

void ResumeList::readFromFiles(const std::string& nameFile, const std::string& scoreFile, const std::string& passwordFile, const std::string& boardStackFile, const std::string& scoreStackFile) {
    std::ifstream nameIn(nameFile, std::ios::binary);
    std::ifstream scoreIn(scoreFile, std::ios::binary);
    std::ifstream passwordIn(passwordFile, std::ios::binary);

    if (!nameIn.is_open() || !scoreIn.is_open() || !passwordIn.is_open()) {
        std::cerr << "Failed to open one or more files for reading." << std::endl;
        return;
    }

    // Clear the current list before loading new data
    while (size > 0)
        removeData(0);

    Player player;
    u32 nameLength = 0;
    u64 score = 0;
    u32 passwordLength = 0;
    std::string name, password;

    while (true) {
        // Read player name
        if (!nameIn.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) break;
        name.resize(nameLength);
        nameIn.read(&name[0], nameLength);

        // Read player score
        if (!scoreIn.read(reinterpret_cast<char*>(&score), sizeof(score))) break;

        // Read player password
        if (!passwordIn.read(reinterpret_cast<char*>(&passwordLength), sizeof(passwordLength))) break;
        password.resize(passwordLength);
        passwordIn.read(&password[0], passwordLength);

        // Set player details
        player.setUserName(name);
        player.setScore(score);
        player.setPassword(password);

        // Initialize empty BoardStack and ScoreStack
        BoardStack boardStack;
        ScoreStack scoreStack;

        boardStack.readFromBinaryFile(boardStackFile);
        scoreStack.readFromBinaryFile(scoreStackFile);

        // Add data to the list
        addData(player, boardStack, scoreStack);
    }

    nameIn.close();
    scoreIn.close();
    passwordIn.close();
}

