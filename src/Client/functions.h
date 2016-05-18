#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>

inline sf::Vector2f dot(sf::Vector2f a, sf::Vector2f b) {
	return{ a.x*b.x,a.y*b.y };
}

inline sf::Vector2f normalize(sf::Vector2f a) {
	float module = magnitude(a);
	if (module == 0) return{ 0.0f, 0.0f};
	else return{a.x/module, a.y/module};
}

inline float RadToDeg(float Rad)
{
	return Rad / M_PI * 180.f;
}

inline float magnitude(sf::Vector2f a) {
	return sqrt((a.x*a.x) + (a.y*a.y));	
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}
