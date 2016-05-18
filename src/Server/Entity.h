#pragma once
#include "const.h"
#include <SFML\Graphics.hpp>
#include <PROTO\Protocol.h>
#include <string>

struct Entity
{
	int uid;
	sf::Vector2f position;
	sf::Vector2f dir;
	int hp;
	void update();
	bool isUser();
	entityData getData();
	virtual std::string getName() = 0;
};

