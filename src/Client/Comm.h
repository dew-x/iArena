#pragma once
#include <SFML\Network.hpp>
#include "const.h"
#include <string>
#include <PROTO\Protocol.h>
#include <vector>
using namespace std;

class Comm
{
public:
	Comm(sf::IpAddress server);
	~Comm();
	void init();
	bool empty();
	Message poll();
	bool send(Message m);
	void stop();
private:
	sf::IpAddress server;
	sf::UdpSocket socket;
	bool end;
	vector<Message> queue;
};

