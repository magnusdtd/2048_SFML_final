#include "Cell.hpp"

Cell::Cell() {
	value = 0;
	rect.setFillColor(colors[0]);
	text.setFillColor(colors[0]);
	text.setString(std::to_string(value));
}

bool Cell::operator==(const Cell& c) const {
	return value == c.value;
}

void Cell::operator=(const Cell& c) {
	value = c.value;
	text.setString(std::to_string(value));
	if (value == 0) {
		rect.setFillColor(colors[0]);
		text.setFillColor(colors[0]);
	}
	else {
		rect.setFillColor(colors[(u64)log2(value)]);
		text.setFillColor(sf::Color::Black);
	}
}

void Cell::operator*=(const u64& val) {
	value *= val;
	text.setString(std::to_string(value));
	if (value == 0) {
		this->rect.setFillColor(colors[0]);
		text.setFillColor(colors[0]);
	}
	else {
		rect.setFillColor(colors[(u64)log2(value)]);
		text.setFillColor(sf::Color::Black);
	}
}

void Cell::init(float posX, float posY, sf::Font& font, float size) {
	value = 0;
	
	text.setFont(font);
	text.setString(std::to_string(value));
	text.setCharacterSize(24);

	rect.setSize(sf::Vector2f(size, size));
	rect.setPosition(posX, posY);
	rect.setFillColor(colors[0]);
	rect.setOutlineThickness(2.f);
	rect.setOutlineColor(sf::Color::Black);

	text.setPosition(posX + 54.f / 2.f, posY + 54.f / 2.f - 5.f);
	text.setFillColor(colors[0]);
}

void Cell::setValue(u64 val) {
	value = val;
	text.setString(std::to_string(value));
	if (value == 0) {
		rect.setFillColor(colors[0]);
		text.setFillColor(colors[0]);
	}
	else {
		rect.setFillColor(colors[(u64)log2(value)]);
		text.setFillColor(sf::Color::Black);
	}
}

u64 Cell::getValue() const {
	return value;
}

void Cell::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
	rt.draw(rect, rs);
	rt.draw(text, rs);
}
