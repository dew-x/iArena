#pragma once
#include <SFML\System.hpp>
#include <vector>
#include <iostream>

struct hitData {
	int uid;
	unsigned damage;
	char kill;
	short hpleft;
	short drop;
};

struct entityData {
	int id;
	float x, y;
	char direction;
	short bearing;
	short hp;
	char name[12];
};

struct itemData {
	short x, y, id;
};

struct bulletData {
	short x, y, bearing;
};

struct Message {
	enum Type {
		NONE,
		BROADCAST,
		REQUEST_LOGIN,
		LOGIN,
		SPAWN,
		UPDATE_KEYS,
		NOTIFY_KEYS,
		FIRE_WEAPON,
		FIRE_RESULT,
		UPDATE_STATE,
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
			int entityCount;
			entityData entities[15];
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
		struct {
			int entityCount;
			entityData entities[10];
			int itemCount;
			itemData items[5];
			int bulletCount;
			bulletData bullets[10];
		} broadcast;
		struct {
			int id;
			float x, y;
			char name[12];
		} spawn;
		struct {
			entityData data;
		} uState;
	} As;
};

class Protocol
{
private:
	static sf::Clock _clock;
	static unsigned id;
public:
	static int now();
	static const Message decode(const char *msg);
	static const char* encode(const Message &m);
	static Message rLogin(const char nick[12]);
	static Message Login(unsigned uid, float x, float y, const std::vector<entityData> &others);
	static Message uKeys(bool w, bool a, bool s, bool d);
	static Message nKeys(unsigned rid);
	static Message fireWeapon(float x, float y, int id);
	static Message fireResult(std::vector<hitData> collisions);
	static Message spawn(float x, float y, int id, const char nick[12]);
	static Message updateState(const entityData &data);
	static Message make(Message::Type type);
};

