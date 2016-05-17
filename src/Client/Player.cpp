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
	acceleration = { 0.0f,0.0f };
	velocity = { 0.0f,0.0f };
	V0 = { 0.0f,0.0f };
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
	/*direction.x = dir.x;
	direction.y = dir.y;*/

}

//setAcceleration
//input -> vector2f, dir of acceleration
//set aMul multiplayer  and set acceleration 
void Player::setAcceleration(sf::Vector2f dir){	
	int sgax = sgn(acceleration.x);
	int sgay = sgn(acceleration.y);
	int sgdx = sgn(dir.x);
	int sgdy = sgn(dir.y);
	if (sgax != sgdx) acceleration.x = (sgax - sgdx) * ACELERATION;
	if (sgay != sgdy) acceleration.y = (sgay - sgdy) * ACELERATION;
	
}

//void Player::updatePos(float dt){
//	aMul.x = std::min(1.0f, aMul.x + 0.01f*dt);
//	aMul.y = std::min(1.0f, aMul.y + 0.01f*dt);
//	position.x += ((direction.x +acceleration.x*aMul.x)*dt)*SPEED;
//	position.y += ((direction.y + acceleration.x*aMul.y)*dt)*SPEED;
//	ps.setPosition(position);
//}

void Player::updatePos(float dt) {
	position += velocity*dt + (acceleration*dt*dt)*0.5f;
	velocity += acceleration * dt;
	velocity.x = std::min(velocity.x,SPEED);
	velocity.y = std::min(velocity.y, SPEED);
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

//float Player::getVelocity()
//{
//	return ;
//}

//void Player::rectificateA(float dt) {
//	sf::Vector2f distance1 = (V0*dt) + ((acceleration*dt*dt)*0.5f);
//	float deltaT = -((2 * distance1) / velocity - SPEED);
//	float a = (SPEED - velocity) / deltaT;
//	setAceleration(a);
//}

void Player::setAceleration(sf::Vector2f a){
	acceleration = a;
}

