#include "Loader.hpp"

u64 Input::loadScoreAndGetMaxScore(u64 order_number) {
	std::fstream input;
	input.open(DATABASE, std::ios::in);

	u64 temp_k = 0, tempScore = 0;
	std::string tempStr;
	u64 tempMaxScore = 0;
	while (!input.eof()) {
		input >> tempStr;
		if (tempStr == "")
			break;
		input >> tempScore;
		temp_k++;
		if (tempScore > tempMaxScore) tempMaxScore = tempScore;
	}
	order_number = temp_k - 1;
	return tempMaxScore;

	input.close();
}

u64 Input::loadBestScore()
{
	u64 bestScore;
	std::ifstream in(BESTSCORE);
	in >> bestScore;
	if (!in.is_open()) {
		std::cout << "Error loading best score\n";
		return 0;
	}
	return (bestScore == 14757395258967641292) ? 0 : bestScore;

	in.close();
}

void Input::saveBestScore(u64 score)
{
	std::ofstream out(BESTSCORE);
	out << score;

	out.close();
}
