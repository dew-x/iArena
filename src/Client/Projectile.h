#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "const.h"
#include "functions.h"

class Projectile : public sf::Drawable
{	
public:
	Projectile();
	Projectile(sf::Vector2f position, sf::Vector2f dir, float size, int id);
	Projectile(const Projectile &projectile);
	~Projectile();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void loadSprite(float size);
	void updatePos(float dt);

private:
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::Vector2f velocity;

	Projectile *proj;

	int id;
	
	//sprite of player
	sf::Texture t;
	sf::Sprite ps;
};

