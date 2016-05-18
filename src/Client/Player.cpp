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

	//signs of acceleration and direction
	int sgax = sgn(acceleration.x);
	int sgay = sgn(acceleration.y);
	int sgdx = sgn(dir.x);
	int sgdy = sgn(dir.y);

	//print print information
	std::cout << "P0 " << position.x << " " << position.y << std::endl;
	std::cout << "V0 " << velocity.x << " " << velocity.y << std::endl;
	std::cout << "A0 " << acceleration.x << " " << acceleration.y << std::endl;

	//if signs of direction and acceleration are diferents, update acceleration with new sign
	if (sgax != sgdx) {
		acceleration.x = (sgdx - sgax) * ACELERATION;
		V0.x = velocity.x;
	}

	if (sgay != sgdy) {
		acceleration.y = (sgdy - sgay) * ACELERATION;
		V0.y = velocity.y;

	}

	std::cout << "P1 " << position.x << " " << position.y << std::endl;
	std::cout << "V1 " << velocity.x << " " << velocity.y << std::endl;
	std::cout << "A1 " << acceleration.x << " " << acceleration.y << std::endl;
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

	if (acceleration.x > 0.0f) velocity.x = std::max(std::min(velocity.x, SPEED), 0.0f);
	else velocity.x = std::max(std::min(velocity.x, 0.0f), -SPEED);
	

	if(acceleration.y > 0.0f) velocity.y = std::max(std::min(velocity.y, SPEED),0.0f);
	else velocity.y = std::max(std::min(velocity.y, 0.0f), -SPEED);
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


void Player::rectificateA(float dt , sf::Vector2f dir) {
	sf::Vector2f vf = dir * SPEED;
	if (sgn(acceleration.x) == sgn(dir.x) && (velocity.x - vf.x) != 0.0f) {
		float distance1 = (V0.x*dt) + ((acceleration.x*dt*dt)*0.5f);
		float deltaT = -((2 * distance1) / (velocity.x - vf.x));
		acceleration.x = (vf.x - velocity.x) / deltaT;

		// segon metode
		/*float distance1 = (V0.x*dt) + ((acceleration.x*dt*dt)*0.5f);
		acceleration.x = ((VF.x-V0.x)*(VF.x-V0.x)*1.5f) / distance1;*/

		//tercer metode
		/*float distance1 = (V0.x*dt) + ((acceleration.x*dt*dt)*0.5f);
		acceleration.x = (deltaV.x * (vf.x - V0.x + (deltaV.x / 2))) / distance1;*/
	}
	if (sgn(acceleration.y) == sgn(dir.y) && (velocity.y - vf.y) != 0.0f){
		float distance1 = (V0.y*dt) + ((acceleration.y*dt*dt)*0.5f);
		float deltaT = -((2 * distance1) / (velocity.y - vf.y));
		acceleration.y = (vf.y - velocity.y) / deltaT;

		//segon metode
		/*float distance1 = (V0.y*dt) + ((acceleration.y*dt*dt)*0.5f);
		acceleration.y = ((VF.y - V0.y)*(VF.y - V0.y)*1.5f) / distance1;*/

		//tercer metode
	/*	float distance1 = (V0.y*dt) + ((acceleration.y*dt*dt)*0.5f);
		acceleration.y = (deltaV.y * (vf.y - V0.y + (deltaV.y/2))) / distance1;*/
	}
	std::cout << "P " << position.x << " " << position.y << std::endl;
	std::cout << "V " << velocity.x << " " << velocity.y << std::endl;
	std::cout <<"A "<< acceleration.x << " " << acceleration.y << std::endl;
}



