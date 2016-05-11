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
	deltaClock = sf::Clock();


	//load images
	if (!b.loadFromFile("textures/grass.jpg"))
	{
		// error...
	}
	background.setTexture(b);
	background.setPosition(0, 0);


	//create scope
	sf::Texture s;
	if (!s.loadFromFile("textures/scope.gif"))
	{
		// error...
	}
	
	scope.setTexture(s);
	scope.setOrigin(scope.getLocalBounds().width / 2, scope.getLocalBounds().height / 2);
	app.setMouseCursorVisible(false);
	


	
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
		sf::Time dt = deltaClock.restart();
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
				else if (scene == SCENE_GAME) {
					if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D) {
						updateMovement();
					}

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
				else if (scene == SCENE_GAME) {
					if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D) {
						updateMovement();
					}
				}
			}
		}
		app.clear(sf::Color(0,0,0,128));
		if (scene == SCENE_LOGIN) {
			drawLogin();
		}
		else if (scene == SCENE_LOADING) {
			drawLoading();
		}
		else if (scene == SCENE_GAME) {
			doGame(dt);
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
				P = new Player(m.As.Login.uid, m.As.Login.x, m.As.Login.y, width*0.05f);
				break;
			}
		}
	}
}

void Game::doGame(sf::Time dt)
{
	updateGame(dt);
	drawGame();	
}

void Game::updateGame(sf::Time dt) {
	P->updatePos(dt.asMilliseconds());
	//sf::Vector2i mousePos = sf::Mouse
	scope.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
}

void Game::drawGame() {
	//app.clear();
	//draw screen
	/*sf::RectangleShape rec({ (float)width,(float)height });
	rec.setFillColor(sf::Color::Blue);
	app.draw(rec);*/
	app.draw(background);

	//draw shape
	sf::View view(sf::FloatRect(0, 0, (float)width, (float)height));
	view.setCenter(width / 2.0f, height / 2.0f);
	view.move({ -width / 2.0f, -height / 2.0f });
	app.setView(view);
	app.draw(*P);

	// draw enemies

	//draw other players
	app.setView(app.getDefaultView());

	app.draw(scope);
}

void Game::updateMovement(){
	Message m = Protocol::uKeys(
		sf::Keyboard::isKeyPressed(sf::Keyboard::W), 
		sf::Keyboard::isKeyPressed(sf::Keyboard::A), 
		sf::Keyboard::isKeyPressed(sf::Keyboard::S), 
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)
	);
	C->send(m);
	sf::Vector2f dir = { 0.0f,0.0f };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		dir.y -= 1.0f;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		dir.x -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		dir.y += 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dir.x += 1.0f;
	}
	P->setDirection(dir);

}
