#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "const.h"
#include "functions.h"

class Projectile : public sf::Drawable
{	
public:
	Projectile();
	void init(sf::Vector2f position, sf::Vector2f dir, float size, int id, sf::Texture &p);
	~Projectile();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void updatePos(float dt);

private:
	void loadSprite(float size);
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::Vector2f velocity;

	Projectile *proj;

	int id;
	
	//sprite of player
	sf::Texture t;
	sf::Sprite ps;
};

