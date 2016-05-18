#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "const.h"
#include <thread>
#include "Comm.h"
#include "Player.h"
#include "Map.h"
#include "projectile.h"
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

	Map *M;

	vector<Message> orders;
	vector<Projectile> projectiles;
	int projectileID;

	//sprites
	sf::Texture b;
	sf::Texture s;
	sf::Texture p;
	sf::Sprite scope;
	sf::Sprite background;
	
};

