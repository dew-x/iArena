#pragma once
#include <SFML\Network.hpp>
#include <string>
#include <PROTO\Protocol.h>
using namespace std;

struct User {
	sf::IpAddress ip;
	unsigned short port;
	int ts;
	string nick;
	int uid;
	float x, y;
	Message message(const Message &m);
};

