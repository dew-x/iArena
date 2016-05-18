#pragma once
#include <SFML\System.hpp>
#include <vector>
#include <iostream>

struct hitData {
	int uid;
	unsigned damage;
	bool kill;
	int hpleft;
	int drop;
};

struct Message {
	enum Type {
		NONE,
		REQUEST_LOGIN,
		LOGIN,
		UPDATE_KEYS,
		NOTIFY_KEYS,
		FIRE_WEAPON,
		FIRE_RESULT,
		MAX
	};
	Message::Type t;
	int ts;
	unsigned uid;
	union
	{
		struct {
			char nick[12];
		} rLogin;
		struct {
			unsigned uid;
			float x;
			float y;
		} Login;
		struct {
			unsigned w, a, s, d;
		} uKeys;
		struct {
			unsigned rid;
		} nKeys;
		struct {
			float x, y;
			int id;
		} wFire;
		struct {
			int pid;
			int size;
			hitData hits[10];
		} rFire;
	} As;
};

class Protocol
{
private:
	static sf::Clock _clock;
	static unsigned id;
	static Message make(Message::Type type);
public:
	static int now();
	static const Message decode(const char *msg);
	static const char* encode(const Message &m);
	static Message rLogin(const char nick[12]);
	static Message Login(unsigned uid, float x, float y);
	static Message uKeys(bool w, bool a, bool s, bool d);
	static Message nKeys(unsigned rid);
	static Message fireWeapon(float x, float y, int id);
	static Message fireResult(std::vector<hitData> collisions);
};

