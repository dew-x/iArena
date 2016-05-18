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
	Enemy(int id, float x, float y, const char name[12], sf::Texture &tex, float size);
	~Enemy();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setEncodedDirection(char encoded);
	void update(float delta);
	int getID() { return id; };
	void updateState(const entityData &state);
private:
	sf::Vector2f position;
	sf::Vector2f direction;
	float hp;
	string name;
	int id;
	sf::Sprite s;
};

