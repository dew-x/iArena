#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "const.h"
#include <string>
#include <PROTO\Protocol.h>
#include <unordered_map>
#include "User.h"
#include <Windows.h>
using namespace std;

typedef unordered_map<string, User>::const_iterator iter;

class Server
{
public:
	Server(unsigned port);
	~Server();
	void run();
private:
	sf::UdpSocket socket;
	unsigned port;
	unordered_map<string,User> users;
};

