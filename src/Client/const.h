#pragma once
const int port = 50000;
const unsigned BUFSIZE = 512;
const unsigned NICKSIZE = 12;
const unsigned MINNICK = 3;
const char SERVERIP[10] = "localhost";
const unsigned MWIDTH = 1000;
const unsigned MHEIGHT = 1000;
const unsigned MSIZE = 100;
const float SPEED = 0.3f;

const float M_PI = 3.1415927410125732421875;

inline float RadToDeg(float Rad)
{
	return Rad / M_PI * 180.f;
}

