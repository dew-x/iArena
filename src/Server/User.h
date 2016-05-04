#pragma once
#include <SFML\Network.hpp>
#include <string>
#include <PROTO\Protocol.h>
using namespace std;

class User
{
public:
	User(sf::IpAddress ip, unsigned short port, int ts, const char nick[12]);
	~User();
	void message(sf::UdpSocket *socket, const Message &m);
	User(const User& other);
private:
	sf::IpAddress ip;
	unsigned short port;
	int ts;
	string nick;
};

