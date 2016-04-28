#include "Game.h"



Game::Game()
{
	
}


Game::~Game()
{
}

void Game::run()
{
	width = sf::VideoMode::getDesktopMode().width;
	height = sf::VideoMode::getDesktopMode().height;
	app = new sf::Window(sf::VideoMode::getDesktopMode(), "GAME", sf::Style::Fullscreen);
	cout << width << " " << height << endl;
	app->setVerticalSyncEnabled(true);
	//app->setFramerateLimit(60);
	while (app->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (app->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				app->close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape || event.key.alt && event.key.code == sf::Keyboard::F4) {
					app->close();
				}
			}
		}
	}
}
