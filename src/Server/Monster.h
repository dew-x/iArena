#pragma once
#include "Entity.h"
#include <map>
#include <string>
using namespace std;

struct Monster : public Entity
{
	void think(map<int, Entity*> entities);
	virtual string getName();
};

