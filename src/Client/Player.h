#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "const.h"
#include "functions.h"

class Player : public sf::Drawable
{

public:
	Player(unsigned uid, float x, float y, float size, std::string nick, const sf::Font &f, short hp);
	~Player();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setDirection(sf::Vector2f dir);
	void setAcceleration(sf::Vector2f dir);
	void updatePos(float dt);
	void loadSprite(float size);
	void setRotation(float angle);
	sf::Vector2f getPosition();
	void rectificateA(float dt, sf::Vector2f dir);
	int getUID() { return uid; };
	void dealDamage(unsigned damage) { hp -= damage; if (hp <= 0) restart(); };
	void restart() {
		position = { 1000.0f, 1000.0f };
		direction = { 0.0f, 0.0f };
		acceleration = { 0.0f,0.0f };
		velocity = { 0.0f,0.0f };
		V0 = { 0.0f,0.0f };
		hp = 100;
	};
private:
	sf::Vector2f direction;
	sf::Vector2f position;
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f V0;
	//sprite of player
	sf::Texture t;
	sf::Sprite ps;
	sf::Text nameText;
	sf::RectangleShape hpbg;
	sf::RectangleShape hpfront;
	int uid;
	int hp;
};

