#pragma once
#include <SFML\Graphics.hpp>
#include "const.h"

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
	//float getVelocity();
	void rectificateA(float dt);
	void setAceleration(sf::Vector2f a);
private:

	sf::CircleShape circle;

	sf::Vector2f direction;
	sf::Vector2f position;
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f V0;
	sf::Vector2f aMul;

	//sprite of player
	sf::Texture t;
	sf::Sprite ps;
};

