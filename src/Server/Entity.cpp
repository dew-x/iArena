#include "Entity.h"

void Entity::update()
{
	position += dir * SPEED;
}

bool Entity::isUser()
{
	return uid>=0;
}

entityData Entity::getData()
{
	entityData d;
	d.x = position.x;
	d.y = position.y;
	d.id = uid;
	char encodedDir = 0;
	if (dir.x > 0) encodedDir |= 1 << 0;
	else if (dir.x < 0) encodedDir |= 1 << 1;
	if (dir.y > 0) encodedDir |= 1 << 2;
	else if (dir.y < 0) encodedDir |= 1 << 3;
	d.direction = encodedDir;
	short encodedBearing = 0;
	d.bearing = encodedBearing;
	d.hp = hp;
	strcpy_s(d.name, 12, getName().c_str());
	return d;
}
