#pragma once
#include <SFML\Main.hpp>
#include <math.h>

inline float distanceLineToPoint(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p0) {
	float y21 = p2.y - p1.y;
	float x21 = p2.x - p1.x;
	float up = y21*p0.x - x21*p0.y + p2.x*p1.y - p2.y*p1.x;
	float down = sqrt(y21*y21 + x21*x21);
	return abs(up / down);
}

inline sf::Vector2f dot(sf::Vector2f a, sf::Vector2f b) {
	return{ a.x*b.x,a.y*b.y };
}

inline float cross(sf::Vector2f a, sf::Vector2f b) {
	return a.x*b.x + a.y*b.y;
}

inline float magnitude(sf::Vector2f a) {
	return sqrt((a.x*a.x) + (a.y*a.y));
}