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

Message Protocol::rLogin(const char nick[12])
{
	Message m;
	m.t = Message::REQUEST_LOGIN;
	m.ts = now();
	strcpy_s(m.As.rLogin.nick, 12, nick);
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

Message Protocol::uKeys(bool w, bool a, bool s, bool d)
{
	Message m;
	m.t = Message::UPDATE_KEYS;
	m.ts = now();
	m.As.uKeys.w = w;
	m.As.uKeys.a = a;
	m.As.uKeys.s = s;
	m.As.uKeys.d = d;
	return m;
}

Message Protocol::nKeys()
{
	return make(Message::NOTIFY_KEYS);
}

int Protocol::now()
{
	return _clock.getElapsedTime().asMilliseconds();
}

Message Protocol::make(Message::Type type)
{
	Message m;
	m.t = type;
	m.ts = now();
	return m;
}

sf::Clock Protocol::_clock = sf::Clock();
