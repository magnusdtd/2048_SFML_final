#include "Setting.hpp"

Setting::Setting() : 
	whichButton(0), mode(Game::MODE_4), buttonOnOff(0), buttonMode(0) {
	// Initialize setting elements...
	if (!font.loadFromFile("Fonts/Heavitas.ttf"))
		std::cout << "Can't load Fonts/Heavitas.ttf";

	backgroundTextureSetting.loadFromFile("Texture/Setting.png");
	backgroundSetting.setTexture(backgroundTextureSetting);

	textMode.setFont(font);
	textMode.setString(std::to_string(mode));
	textMode.setCharacterSize(64);
	textMode.setFillColor(sf::Color(0, 0, 0));
	textMode.setPosition(816.f, 332.f);

	textOnOff.setFont(font);
	textOnOff.setString("Off"); // Default for Undo/Redo function
	textOnOff.setCharacterSize(64);
	textOnOff.setFillColor(sf::Color(0, 0, 0));
	textOnOff.setPosition(829.f, 508.f);

	pressTime = PRESS_DELAY;
	canUndoRedo = false; // Default;
}

void Setting::update(float deltaTime)
{
	pressTime -= deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pressTime <= 0.f) {
		whichButton = (whichButton + 1) % 2;
		pressTime = PRESS_DELAY;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pressTime <= 0.f) {
		whichButton = (whichButton + 1) % 2;
		pressTime = PRESS_DELAY;
	}

	if (whichButton) { // whichButton == 1 => Choose turn on Undo/Redo
		textOnOff.setFillColor(sf::Color(255, 0, 0));
		textMode.setFillColor(sf::Color(0, 0, 0));
	}
	else {
		textMode.setFillColor(sf::Color(255, 0, 0));
		textOnOff.setFillColor(sf::Color(0, 0, 0));
	}

	// Button on/off
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && whichButton && pressTime <= 0.f) {
		buttonOnOff = (buttonOnOff + 1) % 2;
		pressTime = PRESS_DELAY;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && whichButton && pressTime <= 0.f) {
		buttonOnOff = (buttonOnOff + 1) % 2;
		pressTime = PRESS_DELAY;
	}
	// Button mode
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !whichButton && pressTime <= 0.f) {
		buttonMode = (buttonMode + 6) % 7;
		pressTime = PRESS_DELAY;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !whichButton && pressTime <= 0.f) {
		buttonMode = (buttonMode + 1) % 7;
		pressTime = PRESS_DELAY;
	}

	textOnOff.setString((buttonOnOff) ? "On" : "Off");
	canUndoRedo = (buttonOnOff == 1) ? true : false;

	switch (buttonMode) {
	case 0:
		textMode.setString("4");
		mode = Game::MODE_4;
		break;
	case 1:
		textMode.setString("5");
		mode = Game::MODE_5;
		break;
	case 2:
		textMode.setString("6");
		mode = Game::MODE_6;
		break;
	case 3:
		textMode.setString("7");
		mode = Game::MODE_7;
		break;
	case 4:
		textMode.setString("8");
		mode = Game::MODE_8;
		break;
	case 5:
		textMode.setString("9");
		mode = Game::MODE_9;
		break;
	case 6:
		textMode.setString("10");
		mode = Game::MODE_10;
		break;
	}
}

void Setting::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSetting, states);
	target.draw(textMode, states);
	target.draw(textOnOff, states);
}
