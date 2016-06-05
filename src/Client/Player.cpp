#include "Player.h"



Player::Player(unsigned uid, float x, float y , float size, std::string nick, const sf::Font &f)
{
	direction = { 0.0f, 0.0f };
	position.x = x;
	position.y = y;
	loadSprite(size);
	acceleration = { 0.0f,0.0f };
	velocity = { 0.0f,0.0f };
	V0 = { 0.0f,0.0f };
	nameText = sf::Text(nick, f, (unsigned)(size / 8.0f));
	nameText.setOrigin({ nameText.getLocalBounds().width / 2.0f,nameText.getLocalBounds().height / 2.0f + size/2.0f });
	nameText.setColor(sf::Color::Red);
	nameText.setPosition(position);
}


Player::~Player()
{
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::View view = target.getView();
	
	target.draw(ps);
	target.draw(nameText);
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
	int nx = abs(sgn(dir.x));
	int ny = abs(sgn(dir.y));
	int ox = sgn(direction.x);
	int oy = sgn(direction.y);
	//print print information
	std::cout << "P0 " << position.x << " " << position.y << std::endl;
	std::cout << "V0 " << velocity.x << " " << velocity.y << std::endl;
	std::cout << "A0 " << acceleration.x << " " << acceleration.y << std::endl;

	//if signs of direction and acceleration are diferents, update acceleration with new sign
	if (nx != ox) {
		acceleration.x = (nx - ox) * ACELERATION;
		V0.x = velocity.x;
	}

	if (ny != oy) {
		acceleration.y = (ny - oy) * ACELERATION;
		V0.y = velocity.y;
	}

	std::cout << "P1 " << position.x << " " << position.y << std::endl;
	std::cout << "V1 " << velocity.x << " " << velocity.y << std::endl;
	std::cout << "A1 " << acceleration.x << " " << acceleration.y << std::endl;

	direction = dir;
	direction = normalize(direction);
}

//void Player::updatePos(float dt){
//	aMul.x = std::min(1.0f, aMul.x + 0.01f*dt);
//	aMul.y = std::min(1.0f, aMul.y + 0.01f*dt);
//	position.x += ((direction.x +acceleration.x*aMul.x)*dt)*SPEED;
//	position.y += ((direction.y + acceleration.x*aMul.y)*dt)*SPEED;
//	ps.setPosition(position);
//}

void Player::updatePos(float dt) {
	velocity += acceleration * dt;
	velocity.y = std::max(std::min(velocity.y, SPEED), 0.0f);
	velocity.x = std::max(std::min(velocity.x, SPEED), 0.0f);
	/*if (direction.x > 0.0f) velocity.x = std::max(std::min(velocity.x, SPEED), 0.0f);
	else velocity.x = std::max(std::min(velocity.x, 0.0f), -SPEED);


	if (direction.y > 0.0f) velocity.y = std::max(std::min(velocity.y, SPEED), 0.0f);
	else velocity.y = std::max(std::min(velocity.y, 0.0f), -SPEED);*/

	position += dot(direction,velocity*dt);
	
	ps.setPosition(position);
	nameText.setPosition(position);
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
	sf::Vector2f vf = { SPEED*fabs(dir.x),SPEED*fabs(dir.y) };
	if (sgn(dir.x) == sgn(direction.x) && (velocity.x - vf.x) != 0.0f) {
		float distance1 = (V0.x*dt) + ((acceleration.x*dt*dt)*0.5f);
		float deltaT = -((2 * distance1) / (velocity.x - vf.x));
		acceleration.x = (vf.x - velocity.x) / deltaT;
	}
	if (sgn(dir.y) == sgn(direction.y) && (velocity.y - vf.y) != 0.0f) {
		float distance1 = (V0.y*dt) + ((acceleration.y*dt*dt)*0.5f);
		float deltaT = -((2 * distance1) / (velocity.y - vf.y));
		acceleration.y = (vf.y - velocity.y) / deltaT;
	}
	std::cout << "P " << position.x << " " << position.y << std::endl;
	std::cout << "V " << velocity.x << " " << velocity.y << std::endl;
	std::cout <<"A "<< acceleration.x << " " << acceleration.y << std::endl;
}





