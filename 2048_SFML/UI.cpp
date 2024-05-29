#include "UI.hpp"

UI::UI() {
	bestScore = Input::loadBestScore();

	if (!font.loadFromFile("resources/font.ttf"))
		std::cout << "Error loading font\n";

	textBestScore.setFont(font);
	textBestScore.setString(std::to_string(bestScore));
	textBestScore.setCharacterSize(32);
	textBestScore.setFillColor(sf::Color(0, 0, 0));
	textBestScore.setOrigin(textBestScore.getGlobalBounds().width / 2, textBestScore.getGlobalBounds().height / 2);
	textBestScore.setPosition(1010.f, 365.f);

	textScore.setFont(font);
	textScore.setString(std::to_string(score));
	textScore.setCharacterSize(32);
	textScore.setFillColor(sf::Color(0, 0, 0));
	textScore.setOrigin(textScore.getGlobalBounds().width / 2, textScore.getGlobalBounds().height / 2);
	textScore.setPosition(1010.f, 582.f);


	textGameOver.setFont(font);
	textGameOver.setString("Game Over");
	textGameOver.setCharacterSize(35);
	textGameOver.setFillColor(sf::Color(0, 0, 0));
	textGameOver.setOrigin(textGameOver.getGlobalBounds().width / 2, textGameOver.getGlobalBounds().height / 2);
	textGameOver.setPosition(200, 300);

	textResume.setFont(font);
	textResume.setString("Resume");
	textResume.setCharacterSize(35);
	textResume.setFillColor(sf::Color(0, 0, 0));
	textResume.setOrigin(textResume.getGlobalBounds().width / 2, textResume.getGlobalBounds().height / 2);
	textResume.setPosition(200, 300);


	/* Initialize background */
	backgroundTexture.loadFromFile("resources/background.png");
	background.setTexture(backgroundTexture);
	background.setPosition(0.f, 0.f);
}

void UI::GameOver() {
	if (score > bestScore) {
		newScore = true;
		Input::saveBestScore(score);
	}
	else
		gameOver = true;
}

void UI::update(float deltaTime, u64 val) {
	score = val;
	textScore.setString(std::to_string(score));
	textScore.setOrigin(textScore.getGlobalBounds().width / 2, textScore.getGlobalBounds().height / 2);
}

void UI::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	rt.draw(background, rs);

	rt.draw(textBestScore, rs);
	rt.draw(textScore, rs);
	rt.draw(textBestScore, rs);
	rt.draw(textScore, rs);


	if (gameOver) 
		rt.draw(textGameOver, rs);
	if (newScore) 
		rt.draw(textResume, rs);
}

