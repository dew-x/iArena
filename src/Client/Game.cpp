#include "Game.h"



Game::Game()
{
	width = sf::VideoMode::getDesktopMode().width;
	height = sf::VideoMode::getDesktopMode().height;
	app.create(sf::VideoMode::getDesktopMode(), "GAME", sf::Style::Fullscreen);
	app.setVerticalSyncEnabled(true);
	scene = SCENE_LOGIN;
	nickpos = 0;
	memset(nick, 0, NICKSIZE);
	font = sf::Font();
	font.loadFromFile("madpixels.otf");
	typeYourNick = sf::Text("Type your nick:", font, height / 30);
	typeYourNick.setOrigin({ typeYourNick.getLocalBounds().width / 2.0f,typeYourNick.getLocalBounds().height / 2.0f });
	typeYourNick.setPosition({ width / 2.0f,height / 2.2f });
	typeYourNick.setColor(sf::Color::Red);
	uid = -1;
	C = NULL;
	P = NULL;
}


Game::~Game()
{
	if (C != NULL) {
		C->stop();
		T.join();
		delete C;
	}
}

void Game::run()
{
	
	//app->setFramerateLimit(60);
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				app.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape || event.key.alt && event.key.code == sf::Keyboard::F4) {
					app.close();
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				if (scene == SCENE_LOGIN) {
					if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z && nickpos<NICKSIZE-1) {
						nick[nickpos] = (char)((int)'A' + (int)event.key.code);
						++nickpos;
					}
					else if (nickpos>0  && (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Delete)) {
						--nickpos;
						nick[nickpos] = '\0';
					}
					else if (event.key.code == sf::Keyboard::Return) {
						if (nickpos >= MINNICK) {
							commitNick();
						}
					}
				}
			}
		}
		app.clear(sf::Color::Black);
		if (scene == SCENE_LOGIN) {
			drawLogin();
		}
		else if (scene == SCENE_LOADING) {
			drawLoading();
		}
		else if (scene == SCENE_GAME) {
			doGame();
		}
		app.display();
	}
}

void Game::commitNick()
{
	scene = SCENE_LOADING;
	C = new Comm(SERVERIP);
	T = thread(&Comm::init, C);
	if (!C->send(Protocol::rLogin(nick))) {
		app.close();
	}
}

void Game::drawLogin()
{
	sf::Text nickText((string)nick, font, height/30);
	nickText.setOrigin({ nickText.getLocalBounds().width / 2.0f,nickText.getLocalBounds().height / 2.0f });
	nickText.setPosition({ width / 2.0f,height / 2.0f });
	nickText.setColor(sf::Color::Red);
	app.draw(nickText);
	app.draw(typeYourNick);
}

void Game::drawLoading()
{
	if (P != NULL) {
		scene = SCENE_GAME;
	}
	else {
		sf::Text loading("Loading", font, height / 30);
		loading.setOrigin({ loading.getLocalBounds().width,loading.getLocalBounds().height });
		loading.setPosition({(float)width,(float)height });
		loading.setColor(sf::Color::Red);
		app.draw(loading);
		while (!C->empty()) {
			Message m = C->poll();
			if (m.t == Message::LOGIN) {
				P = new Player(m.As.Login.uid, m.As.Login.x, m.As.Login.y);
				break;
			}
		}
	}
}

void Game::doGame()
{
	sf::RectangleShape rec({ (float)width,(float)height });
	rec.setFillColor(sf::Color::Blue);
	app.draw(rec);
}
