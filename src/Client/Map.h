#pragma once
#include <SFML\Graphics.hpp>
#include "const.h"

class Map : public sf::Drawable
{
public:
	Map();
	~Map();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::VertexArray grid;
};

