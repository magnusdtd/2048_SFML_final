#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Loader.hpp"

class UI : public sf::Drawable {
private:
	sf::Font font;
	sf::Text textBestScore;
	sf::Text textScore;
	sf::Text textGameOver;
	sf::Text textResume;
	u64 bestScore = 0;
	u64 score = 0;
	bool newScore = false;
	bool gameOver = false;

	sf::Texture backgroundTexture;
	sf::Sprite background;
public:
	UI();
	void GameOver();
	void update(float deltaTime, u64 score);
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};

#endif
