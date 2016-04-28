#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
using namespace std;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::Window *app;
	int width, height;
};

