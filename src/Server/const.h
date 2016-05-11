#pragma once
const int port = 50000;
const unsigned BUFSIZE = 512;
const float M_PI = 3.1415927410125732421875;

inline float RadToDeg(float Rad)
{
	return Rad / M_PI * 180.f;
}