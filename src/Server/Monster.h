#pragma once
#include "Entity.h"
#include <map>
using namespace std;

struct Monster : public Entity
{
	void think(map<int, Entity*> entities);
};

