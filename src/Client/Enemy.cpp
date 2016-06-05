#include "Enemy.h"


Enemy::Enemy(int id, float x, float y, const char name[12],sf::Texture &tex,float size, const sf::Font &font)
{
	this->id = id;
	position = { x,y };
	direction = { 0.0f,0.0f };
	this->name = name;
	s = sf::Sprite(tex);
	s.setOrigin(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2);
	s.setScale(size / s.getLocalBounds().width, size / s.getLocalBounds().width);
	s.setPosition(position);
	nameText = sf::Text(this->name, font, (unsigned)(size / 4.0f));
	nameText.setOrigin({ nameText.getLocalBounds().width / 2.0f,nameText.getLocalBounds().height / 2.0f + size / 2.0f });
	nameText.setColor(sf::Color::Red);
	nameText.setPosition(position);
}

Enemy::~Enemy()
{
}

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(s);
	target.draw(nameText);
}

void Enemy::setEncodedDirection(char encoded)
{
	if (encoded & 1) direction.x = 1.0f;
	else if (encoded & 2) direction.x = -1.0f;
	else direction.x = 0.0f;
	if (encoded & 4) direction.y = 1.0f;
	else if (encoded & 8) direction.y = -1.0f;
	else direction.y = 0.0f;
}

void Enemy::update(float delta) {
	position += normalize(direction)*SPEED*delta;
	s.setPosition(position);
	nameText.setPosition(position);
}

void Enemy::updateState(const entityData &state)
{
	setEncodedDirection(state.direction);
}
