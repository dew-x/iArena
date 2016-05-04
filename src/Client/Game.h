#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "const.h"
#include <thread>
#include "Comm.h"
#include "Player.h"
using namespace std;

enum scenes {
	SCENE_LOGIN,
	SCENE_LOADING,
	SCENE_GAME,
	SCENE_SCORE
};

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::RenderWindow app;
	sf::Font font;
	sf::Text typeYourNick;
	int width, height;
	int uid;
	scenes scene;
	char nick[NICKSIZE];
	int nickpos;
	void commitNick();
	void drawLogin();
	void drawLoading();
	void doGame(sf::Time dt);
	void updateGame(sf::Time dt);
	void drawGame();
	void updateMovement();
	Comm *C;
	thread T;
	Player *P;
	sf::Clock deltaClock;
};

