#include "projectile.h"

Projectile::Projectile() {
}

void Projectile::init(sf::Vector2f p, sf::Vector2f dir, float size, int id, sf::Texture &tex){
	position = p;
	velocity = dir * (SPEED * 4);
	direction = dir;
	this->id = id;
	ps = sf::Sprite(tex);
	ps.setOrigin(ps.getLocalBounds().width / 2, ps.getLocalBounds().height / 2);
	ps.setScale(size / ps.getLocalBounds().width, size / ps.getLocalBounds().width);
	ps.setPosition(position);
}


Projectile::~Projectile(){
}

void Projectile::draw(sf::RenderTarget & target, sf::RenderStates states) const{
	target.draw(ps);
}

void Projectile::updatePos(float dt){
	position += velocity * dt;
	ps.setPosition(position);
}





