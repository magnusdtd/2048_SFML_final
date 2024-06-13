#ifndef RESUME_LIST_HPP
#define RESUME_LIST_HPP


#include "Player.hpp"
#include "BoardStack.hpp"
#include "ScoreStack.hpp"

class ResumeNode {
public:
	Player player;
	BoardStack boardStack;
	ScoreStack scoreStack;	
	ResumeNode *next;

	ResumeNode() : next(nullptr) {}
};

class ResumeList {
private:
	ResumeNode *head;
	u32 size;
public:
	ResumeList() : head(nullptr), size(0) {}

	~ResumeList();

	void addData(Player player, BoardStack boardStack, ScoreStack scoreStack);

	void removeData(u32 index);

	ResumeNode* getData(u32 index);

	u32 getSize() const;

	void writeToFiles(const std::string& nameFile, const std::string& scoreFile, const std::string& passwordFile, const std::string& boardStackFile, const std::string& scoreStackFile);
};

#endif