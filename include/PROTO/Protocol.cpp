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
	Message m = make(Message::REQUEST_LOGIN);
	strcpy_s(m.As.rLogin.nick, 12, nick);
	return m;
}

Message Protocol::Login(unsigned uid, float x, float y, const std::vector<entityData> &others)
{
	Message m = make(Message::LOGIN);
	m.As.Login.uid = uid;
	m.As.Login.x = x;
	m.As.Login.y = y;
	m.As.Login.entityCount = others.size();
	for (unsigned i = 0; i < others.size(); ++i) {
		m.As.Login.entities[i] = others[i];
	}
	return m;
}

Message Protocol::uKeys(bool w, bool a, bool s, bool d)
{
	Message m = make(Message::UPDATE_KEYS);
	m.As.uKeys.w = w;
	m.As.uKeys.a = a;
	m.As.uKeys.s = s;
	m.As.uKeys.d = d;
	return m;
}

Message Protocol::nKeys(unsigned rid)
{
	Message m = make(Message::NOTIFY_KEYS);
	m.As.nKeys.rid = rid;
	return m;
}

Message Protocol::fireWeapon(float x, float y, int id)
{
	Message m= make(Message::FIRE_WEAPON);
	m.As.wFire.x = x;
	m.As.wFire.y = y;
	m.As.wFire.id = id;
	return m;
}

Message Protocol::fireResult(std::vector<hitData> collisions)
{
	return make(Message::FIRE_RESULT);
}

Message Protocol::spawn(float x, float y, int id, const char nick[12])
{
	Message m = make(Message::SPAWN);
	m.As.spawn.id = id;
	m.As.spawn.x = x;
	m.As.spawn.y = y;
	strcpy_s(m.As.spawn.name, 12, nick);
	return m;
}

Message Protocol::updateState(const entityData & data)
{
	Message m = make(Message::UPDATE_STATE);
	m.As.uState.data = data;
	return m;
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
	m.uid = id++;
	return m;
}

sf::Clock Protocol::_clock = sf::Clock();
unsigned Protocol::id = 0;