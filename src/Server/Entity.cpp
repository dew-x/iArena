#include "Entity.h"

void Entity::update()
{
	position += dir * SPEED;
}

bool Entity::isUser()
{
	return uid>=0;
}
