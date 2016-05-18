#pragma once
#include <SFML\Network.hpp>
#include <SFML\Main.hpp>
#include <string>
#include <PROTO\Protocol.h>
#include <vector>
#include <map>
#include "const.h"
#include "Entity.h"
#include "functions.h"
#include <math.h>
using namespace std;

struct User : public Entity {
	sf::IpAddress ip;
	unsigned short port;
	int ts;
	string nick;
	Message message(const Message &m, map<int, Entity*> entities);
	std::vector<Message> keys;
};

