#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "const.h"
#include "functions.h"

class Player : public sf::Drawable
{

public:
	Player(unsigned uid, float x, float y, float size);
	~Player();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setDirection(sf::Vector2f dir);
	void setAcceleration(sf::Vector2f dir);
	void updatePos(float dt);
	void loadSprite(float size);
	void setRotation(float angle);
	sf::Vector2f getPosition();
	void rectificateA(float dt, sf::Vector2f dir);
	
private:
	sf::Vector2f direction;
	sf::Vector2f position;
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f V0;
	

	//sprite of player
	sf::Texture t;
	sf::Sprite ps;
};

