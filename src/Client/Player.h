#pragma once
#include <SFML\Graphics.hpp>

class Player : public sf::Drawable
{

public:
	Player(unsigned uid, float x, float y, float size);
	~Player();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setDirection(sf::Vector2f dir);
	void updatePos(float dt);
	void loadSprite();
private:

	sf::CircleShape circle;
	sf::Vector2f direction;
	sf::Vector2f position;
	sf::Texture t;
	sf::Sprite ps;
};

