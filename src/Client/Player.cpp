#include "Player.h"



Player::Player(unsigned uid, float x, float y , float size)
{
	circle = sf::CircleShape(size);
	circle.setOrigin({ circle.getLocalBounds().width / 2.0f,circle.getLocalBounds().height / 2.0f });
	circle.setFillColor(sf::Color::Green);
	direction.x = 1.0f;
	direction.y = 0.0f;
	position.x = x;
	position.y = y;
	loadSprite();
}


Player::~Player()
{
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::View view = target.getView();
	
	target.draw(ps);
}

void Player::setDirection(sf::Vector2f dir){
	direction.x = dir.x;
	direction.y = dir.y;
}

void Player::updatePos(float dt){
	position += (direction*dt);
}

void Player::loadSprite(){
	if (!t.loadFromFile("player.gif")) {
		//error
	}

	ps.setTexture(t);
	ps.setPosition(position);
}

void Player::updateDirection(sf::Vector2f mousePosition){
	sf::Vector2f dir = mousePosition - position;
	float length = sqrt((dir.x*dir.x)+(dir.y*dir.y));
	direction = dir / length;
}

