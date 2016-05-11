#include "Player.h"



Player::Player(unsigned uid, float x, float y , float size)
{
	circle = sf::CircleShape(size);
	circle.setOrigin({ circle.getLocalBounds().width / 2.0f,circle.getLocalBounds().height / 2.0f });
	circle.setFillColor(sf::Color::Green);
	direction = { 0.0f, 0.0f };
	position.x = x;
	position.y = y;
	loadSprite(size);
	acceleration = { 0.0f, 0.0f };
	aMul = { 0.0f, 0.0f };
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

//setAcceleration
//input -> vector2f, dir of acceleration
//set aMul multiplayer  and set acceleration 
void Player::setAcceleration(sf::Vector2f dir){
	if (direction.x != dir.x) {
		aMul.x = 0.0f;
	}

	if (direction.y != dir.y) {
		aMul.y = 0.0f;
	}
	acceleration = direction - dir;
}

void Player::updatePos(float dt){
	aMul.x = std::min(1.0f, aMul.x + 0.01f*dt);
	aMul.y = std::min(1.0f, aMul.y + 0.01f*dt);
	position.x += ((direction.x +acceleration.x*aMul.x)*dt)*SPEED;
	position.y += ((direction.y + acceleration.y*aMul.y)*dt)*SPEED;
	ps.setPosition(position);
}

void Player::loadSprite(float size){
	if (!t.loadFromFile("textures/player.gif")) {
		//error
	}

	ps.setTexture(t);
	ps.setOrigin(ps.getLocalBounds().width/2, ps.getLocalBounds().height / 2);
	ps.setScale(size/ps.getLocalBounds().width , size/ ps.getLocalBounds().width );
	ps.setPosition(position);
}

void Player::setRotation(float angle){
	ps.setRotation(angle);
}

sf::Vector2f Player::getPosition()
{
	return position;
}

