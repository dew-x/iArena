#include "User.h"

Message User::message(const Message & m, map<int, Entity*> entities, Message &broadcast, vector<Item> items)
{
	bool valid = true;
	if (m.uid == last + 1) ++last;
	else {
		valid = false;
		cout << "MISSING PACKET" << endl;
	}
	Message res;
	sf::Vector2f ndir = { 0.0f,0.0f }, sdir, edir;
	vector<hitData> collisions(0);
	vector<entityData> others(0);
	res.t = Message::NONE;
	float dist;
	switch (m.t)
	{
	case Message::NONE:
		break;
	case Message::REQUEST_LOGIN:
		for (map<int, Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
			if (it->first != uid) {
				others.push_back(it->second->getData());
			}
		}
		res = Protocol::Login(uid, position.x, position.y, others, 100, items);
		break;
	case Message::LOGIN:
		break;
	case Message::UPDATE_KEYS:
		if (valid) keys.push_back(m);
		res = Protocol::nKeys(m.uid,position.x,position.y);
		if (valid && m.As.uKeys.w) ndir.y -= 1.0f;
		if (valid && m.As.uKeys.a) ndir.x -= 1.0f;
		if (valid && m.As.uKeys.s) ndir.y += 1.0f;
		if (valid && m.As.uKeys.d) ndir.x += 1.0f;
		this->dir = ndir;
		if (valid) broadcast = Protocol::updateState(getData());
		break;
	case Message::NOTIFY_KEYS:
		break;
	case Message::FIRE_WEAPON:
		if (valid) {
			sdir = { m.As.wFire.x, m.As.wFire.y };
			for (map<int, Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
				if (it->first != uid) {
					dist = distanceLineToPoint(position, position + sdir, it->second->position);
					if (dist < RADIUS) {
						sf::Vector2f edir = it->second->position - position;
						float cos = cross(sdir, edir) / (magnitude(sdir)*magnitude(edir));
						if (cos >= 0.0f) {
							it->second->hp -= 10;
							if (it->second->hp <= 0) it->second->restart();
							collisions.push_back({ it->first,10,(char)(it->second->hp > 0),it->second->hp,0 });
						}
					}
				}
			}
			broadcast = Protocol::fireBroadcast(uid, sdir, collisions);
		}
		res = Protocol::fireResult(collisions);
		break;
	case Message::FIRE_RESULT:
		break;
	case Message::MAX:
		break;
	default:
		break;
	}
	res.ack = last;
	return res;
}

string User::getName()
{
	return nick;
}
