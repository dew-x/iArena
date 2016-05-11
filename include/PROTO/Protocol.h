#pragma once
#include <SFML\System.hpp>
#include <iostream>

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
			
		} nKeys;
		struct {
			float x, y;
		} wFire;
		struct {

		} rFire;
	} As;
};

class Protocol
{
private:
	static sf::Clock _clock;
	static int now();
	static Message make(Message::Type type);
public:
	static const Message decode(const char *msg);
	static const char* encode(const Message &m);
	static Message rLogin(const char nick[12]);
	static Message Login(unsigned uid, float x, float y);
	static Message uKeys(bool w, bool a, bool s, bool d);
	static Message nKeys();
	static Message fireWeapon(float x, float y);
	static Message fireResult();
};

