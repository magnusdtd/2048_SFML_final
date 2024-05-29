#ifndef Cell_HPP
#define Cell_HPP

#include <SFML/Graphics.hpp>
#include <string.h>
#include <math.h>
#include "utils.hpp"

class Cell : public sf::Drawable {
private:
	u64 value;
	sf::Text text;
	sf::RectangleShape rect;
	const sf::Color colors[12] = { sf::Color(102,102,102),
									sf::Color(255,166,0),
									sf::Color(245,151,245),
									sf::Color(51,204,153),
									sf::Color(255,110,110),
									sf::Color(255,204,77),
									sf::Color(166,166,255),
									sf::Color(137,194,247),
									sf::Color(0,255,255),
									sf::Color(0,128,0),
									sf::Color(255,0,255),
									sf::Color(128,128,0) };
public:
	Cell();
	bool operator == (const Cell& c) const;
	void operator = (const Cell& c);
	void operator *= (const u64& val);
	void init(float posX, float posY, sf::Font& font, float size);
	void setValue(u64 val);
	u64 getValue() const;
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};

#endif