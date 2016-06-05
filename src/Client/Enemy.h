#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include "const.h"
#include "functions.h"
#include <math.h>
#include <string>
#include <PROTO\Protocol.h>
using namespace std;

class Enemy : public sf::Drawable
{
public:
	Enemy(int id, float x, float y, const char name[12], sf::Texture &tex, float size, const sf::Font &font, short hp);
	~Enemy();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setEncodedDirection(char encoded);
	void update(float delta);
	int getID() { return id; };
	void updateState(const entityData &state);
	sf::Vector2f getPosition();
	void dealDamage(unsigned dmg) { hp -= dmg; if (hp <= 0) restart();};
	void restart() {
		position = { 1000.0f, 1000.0f };
		direction = { 0.0f,0.0f };
		hp = 100;
	};
private:
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::RectangleShape hpbg;
	sf::RectangleShape hpfront;
	short hp;
	string name;
	int id;
	sf::Sprite s;
	sf::Text nameText;
};

