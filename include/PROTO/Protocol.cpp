#include "Protocol.h"

const Message Protocol::decode(const char *msg)
{
	const Message *ret = reinterpret_cast <const Message*>(msg);
	return *ret;
}

const char* Protocol::encode(const Message &m)
{
	return reinterpret_cast<const char*>(&m);
}

Message Protocol::rLogin(const char nick[4])
{
	Message m;
	m.t = Message::REQUEST_LOGIN;
	m.ts = now();
	strcpy_s(m.As.rLogin.nick, sizeof(nick), nick);
	return m;
}

Message Protocol::Login(unsigned uid, float x, float y)
{
	Message m;
	m.t = Message::LOGIN;
	m.ts = now();
	m.As.Login.uid = uid;
	m.As.Login.x = x;
	m.As.Login.y = y;
	return m;
}

int Protocol::now()
{
	return _clock.getElapsedTime().asMilliseconds();
}

sf::Clock Protocol::_clock = sf::Clock();
