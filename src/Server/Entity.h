#pragma once
#include "const.h"
#include <SFML\Graphics.hpp>

struct Entity
{
	int uid;
	sf::Vector2f position;
	sf::Vector2f dir;

	void update();
	bool isUser();
};

