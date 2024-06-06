#ifndef Cell_HPP
#define Cell_HPP

#include <string.h>
#include <math.h>
#include "layout.hpp"

class Cell : public sf::Drawable {
private:
	u64 value;
	sf::Text text;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Cell();
	bool operator == (const Cell& c) const;
	void operator = (const Cell& c);
	void operator *= (const u64& val);
	void init(	float posX,
				float posY,
				sf::Font& font,
				float size,
				float alignX,
				float alignY,
				u32 sizeOfValue);
	void setValue(u64 val);
	u64 getValue() const;
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
};

#endif