#include "Enemy.h"


Enemy::Enemy(int id, float x, float y, const char name[12],sf::Texture &tex,float size, const sf::Font &font, short hp)
{
	todo = { 0,0 };
	this->id = id;
	position = { x,y };
	direction = { 0.0f,0.0f };
	this->name = name;
	s = sf::Sprite(tex);
	s.setOrigin(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2);
	s.setScale(size / s.getLocalBounds().width, size / s.getLocalBounds().width);
	s.setPosition(position);
	nameText = sf::Text(this->name, font, (unsigned)(size / 4.0f));
	nameText.setOrigin({ nameText.getLocalBounds().width / 2.0f,nameText.getLocalBounds().height / 2.0f + size - size / 5.0f });
	nameText.setColor(sf::Color::Red);
	nameText.setPosition(position);
	this->hp = hp;
	hpbg = sf::RectangleShape({ size,size / 5.0f });
	hpbg.setFillColor(sf::Color::Black);
	hpbg.setOrigin({ hpbg.getLocalBounds().width / 2.0f,hpbg.getLocalBounds().height / 2.0f + size*2.0f / 3.0f - size / 5.0f });
	hpfront = sf::RectangleShape({ size - 4,size / 5.0f - 4 });
	hpfront.setFillColor(sf::Color::Red);
	hpfront.setOrigin({ hpfront.getLocalBounds().width / 2.0f,hpfront.getLocalBounds().height / 2.0f + size*2.0f / 3.0f - size / 5.0f });
}

Enemy::~Enemy()
{
}

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(s);
	target.draw(nameText);
	target.draw(hpbg);
	target.draw(hpfront);
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
	sf::Vector2f tomove = normalize(direction)*SPEED*delta+todo*0.1f;
	todo -= todo*0.1f;
	position += tomove;
	s.setPosition(position);
	nameText.setPosition(position);
	hpbg.setPosition(position);
	hpfront.setPosition(position);
	hpfront.setScale({ hp / 100.0f,1 });
}

void Enemy::updateState(const entityData &state)
{
	setEncodedDirection(state.direction);
	todo.x = (state.x - position.x);
	todo.y = (state.y - position.y);
}

sf::Vector2f Enemy::getPosition()
{
	return position;
}
