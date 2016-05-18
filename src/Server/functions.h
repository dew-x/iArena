#pragma once
#include <SFML\Main.hpp>

inline float distanceLineToPoint(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p0) {
	float y21 = p2.y - p1.y;
	float x21 = p2.x - p1.x;
	float up = y21*p0.x - x21*p0.y + p2.x*p1.y - p2.y*p1.x;
	float down = sqrt(y21*y21 + x21*x21);
	return up / down;
}