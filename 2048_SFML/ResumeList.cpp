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


void ResumeList::writeToFiles() {
    ResumeNode* current = head;
    u32 index = 0; // Start index from 0

    while (current != nullptr) {
        // Adjusted filename extension to .data
        std::string filename = "ResumeData/" + std::to_string(index) + ".data";
        std::ofstream fileOut(filename, std::ios::binary);

        if (!fileOut) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            current = current->next;
            ++index;
            continue;
        }

        // Write player name
        size_t nameLength = current->player.getName().length();
        fileOut.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        fileOut.write(current->player.getName().c_str(), nameLength);

        // Write player score
        u64 score = current->player.getScore();
        fileOut.write(reinterpret_cast<const char*>(&score), sizeof(score));

        // Write player password
        size_t passwordLength = current->player.getPassword().length();
        fileOut.write(reinterpret_cast<const char*>(&passwordLength), sizeof(passwordLength));
        fileOut.write(current->player.getPassword().c_str(), passwordLength);

        // Ensure BoardStack and ScoreStack serialization methods handle the new file extension correctly
        current->boardStack.writeToBinaryFile(filename);
        current->scoreStack.writeToBinaryFile(filename);

        fileOut.close();

        current = current->next;
        ++index; // Increment index for the next node
    }
}



void ResumeList::readFromFiles() {
    // Clear the current list before loading new data
    while (size > 0)
        removeData(0);

    u32 index = 0; // Start index from 0
    while (true) {
        // Corrected filename string
        std::string filename = "ResumeData/" + std::to_string(index) + ".dat";
        std::ifstream fileIn(filename, std::ios::binary);

        if (!fileIn) {
            // If the file cannot be opened, assume we've reached the end of the list
            break;
        }

        Player player;
        u32 nameLength = 0;
        u64 score = 0;
        u32 passwordLength = 0;
        std::string name, password;

        // Read player name
        fileIn.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        name.resize(nameLength);
        fileIn.read(&name[0], nameLength);

        // Read player score
        fileIn.read(reinterpret_cast<char*>(&score), sizeof(score));

        // Read player password
        fileIn.read(reinterpret_cast<char*>(&passwordLength), sizeof(passwordLength));
        password.resize(passwordLength);
        fileIn.read(&password[0], passwordLength);

        // Set player details
        player.setUserName(name);
        player.setScore(score);
        player.setPassword(password);

        // Initialize empty BoardStack and ScoreStack
        BoardStack boardStack;
        ScoreStack scoreStack;

        // Assuming BoardStack and ScoreStack have methods to deserialize their data from a binary format
        boardStack.readFromBinaryFile(filename);
        scoreStack.readFromBinaryFile(filename);

        // Add data to the list
        addData(player, boardStack, scoreStack);

        fileIn.close();
        ++index; // Increment index for the next file
    }
}



void ResumeList::clearDataFiles()
{
    std::ofstream outputName("ResumeData\1.dat", std::ios::trunc);
    std::ofstream outputScore("ResumeData\2.dat", std::ios::trunc);
    std::ofstream outputPassword("ResumeData\3.dat", std::ios::trunc);
    std::ofstream outputBoardStack("ResumeData\4.dat", std::ios::trunc);
    std::ofstream outputScoreStack("ResumeData\5.dat", std::ios::trunc);
}

