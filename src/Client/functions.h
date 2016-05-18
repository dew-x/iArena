#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>

inline sf::Vector2f dot(sf::Vector2f a, sf::Vector2f b) {
	return{ a.x*b.x,a.y*b.y };
}

inline sf::Vector2f normalize(sf::Vector2f a) {
	float module = sqrt((a.x*a.x) + (a.y*a.y));
	if (module == 0) return{ 0.0f, 0.0f};
	else return{a.x/module, a.y/module};
}