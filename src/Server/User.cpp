#include "User.h"



User::User(sf::IpAddress ip, unsigned short port, int ts, const char nick[12])
{
	this->ip = ip;
	this->port = port;
	this->ts = ts;
	this->nick = nick;
}


User::~User()
{
}

void User::message(sf::UdpSocket *socket, const Message & m)
{
}

User::User(const User & other)
{
	ip = other.ip;
	port = other.port;
	ts = other.ts;
	nick = other.nick;
}


