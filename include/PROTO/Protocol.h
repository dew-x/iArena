#pragma once
#include <SFML\System.hpp>
#include <iostream>

struct Message {
	enum Type {
		NONE,
		REQUEST_LOGIN,
		LOGIN,
		MAX
	};
	Message::Type t;
	int ts;
	union
	{
		struct {
			char nick[16];
		} rLogin;
		struct {
			unsigned uid;
			float x;
			float y;
		} Login;
	} As;
};

class Protocol
{
private:
	static sf::Clock _clock;
	static int now();
public:
	static const Message decode(const char *msg);
	static const char* encode(const Message &m);
	static Message rLogin(const char nick[16]);
	static Message Login(unsigned uid, float x, float y);
};

