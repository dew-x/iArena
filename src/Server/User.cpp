#include "User.h"

Message User::message(const Message & m)
{
	Message res;
	res.t = Message::NONE;
	switch (m.t)
	{
	case Message::NONE:
		break;
	case Message::REQUEST_LOGIN:
		res = Protocol::Login(uid, x, y);
		break;
	case Message::LOGIN:
		break;
	case Message::UPDATE_KEYS:
		res = Protocol::nKeys();
		break;
	case Message::NOTIFY_KEYS:
		break;
	case Message::MAX:
		break;
	default:
		break;
	}
	return res;
}