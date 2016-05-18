#include "User.h"

Message User::message(const Message & m, map<int, Entity*> entities)
{
	Message res;
	sf::Vector2f ndir = { 0.0f,0.0f };
	res.t = Message::NONE;
	switch (m.t)
	{
	case Message::NONE:
		break;
	case Message::REQUEST_LOGIN:
		res = Protocol::Login(uid, position.x, position.y);
		break;
	case Message::LOGIN:
		break;
	case Message::UPDATE_KEYS:
		keys.push_back(m);
		res = Protocol::nKeys(m.uid);
		if (m.As.uKeys.w) ndir.y -= 1.0f;
		if (m.As.uKeys.a) ndir.x -= 1.0f;
		if (m.As.uKeys.s) ndir.y += 1.0f;
		if (m.As.uKeys.d) ndir.x += 1.0f;
		this->dir = ndir;
		break;
	case Message::NOTIFY_KEYS:
		break;
	case Message::FIRE_WEAPON:
		break;
	case Message::FIRE_RESULT:
		break;
	case Message::MAX:
		break;
	default:
		break;
	}
	return res;
}

