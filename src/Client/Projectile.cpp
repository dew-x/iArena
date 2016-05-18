#include "projectile.h"

Projectile::Projectile() {
}

Projectile::Projectile(sf::Vector2f p, sf::Vector2f dir, float size, int id){
	position = p;
	velocity = dir * (SPEED * 10);
	direction = dir;
	loadSprite(size);
	this->id = id;
	
}

Projectile::Projectile(const Projectile & projectile){
	position = projectile.position;
	velocity = projectile.velocity;
	direction = projectile.direction;
	t = projectile.t;
	ps = projectile.ps;
	id = projectile.id;
}


Projectile::~Projectile(){
}

void Projectile::draw(sf::RenderTarget & target, sf::RenderStates states) const{
	target.draw(ps);
}

void Projectile::loadSprite(float size) {
	if (!t.loadFromFile("textures/fireBall2.png")) {
		//error
	}

	ps.setTexture(t);
	ps.setOrigin(ps.getLocalBounds().width / 2, ps.getLocalBounds().height / 2);
	ps.setScale(size / ps.getLocalBounds().width, size / ps.getLocalBounds().width);
	ps.setPosition(position);
}

void Projectile::updatePos(float dt){
	position += velocity * dt;
	ps.setPosition(position);

}





