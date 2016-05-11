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
	M = NULL;
	orders = vector<Message>(0);
	deltaClock = sf::Clock();


	//load images
	if (!b.loadFromFile("textures/grass.jpg"))
	{
		// error...
	}
	background.setTexture(b);
	background.setPosition(0, 0);


	//create scope
	if (!s.loadFromFile("textures/scope.png"))
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
		delete M;
		delete P;
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

			//mouse event
			else if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Protocol::fireWeapon(sf::Mouse::getPosition().x-(width/2.0f), sf::Mouse::getPosition().y - (height/2.0f));
				}
			}
			
			//key pressed events
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

			//key released events
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
				M = new Map();
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
	P->updatePos((float)dt.asMilliseconds());
	float radians = atan2(sf::Mouse::getPosition().y - height / 2.0f, sf::Mouse::getPosition().x - width / 2.0f);
	P->setRotation(RadToDeg(radians));
	scope.setPosition((float)sf::Mouse::getPosition().x,(float) sf::Mouse::getPosition().y);
	while (!C->empty()) {
		Message m = C->poll();
		
		switch (m.t)
		{
		case Message::NONE:
			break;
		case Message::REQUEST_LOGIN:
			break;
		case Message::LOGIN:
			break;
		case Message::UPDATE_KEYS:
			break;
		case Message::NOTIFY_KEYS:
			for (unsigned i = 0; i < orders.size(); i++) {
				if (orders[i].uid == m.As.nKeys.rid) {
					int delta = Protocol::now()-orders[i].ts;
					cout << delta << endl;
					sf::Vector2f dir = { 0.0f,0.0f };
					if (orders[i].As.uKeys.w) {
						dir.y -= 1.0f;
					}
					if (orders[i].As.uKeys.a) {
						dir.x -= 1.0f;
					}
					if (orders[i].As.uKeys.s) {
						dir.y += 1.0f;
					}
					if (orders[i].As.uKeys.d) {
						dir.x += 1.0f;
					}
					P->setDirection(dir);
				}
			}
			break;
		case Message::FIRE_WEAPON:
			break;
		case Message::FIRE_RESULT:
			break;
		case Message::MAX:
			break;
		default:
			break;
		}
	}
}

void Game::drawGame() {
	//app.clear();
	//draw screen
	/*sf::RectangleShape rec({ (float)width,(float)height });
	rec.setFillColor(sf::Color::Blue);
	app.draw(rec);*/
	//app.draw(background);

	//draw shape
	sf::View view(sf::FloatRect(0, 0, (float)width, (float)height));
	sf::Vector2f Ppos = P->getPosition();
	view.setCenter(width / 2.0f, height / 2.0f);
	view.move({ -width / 2.0f + Ppos.x, -height / 2.0f + Ppos.y });
	app.setView(view);
	app.draw(*M);
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
	orders.push_back(m);
	/*sf::Vector2f dir = { 0.0f,0.0f };
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
	P->setAcceleration(dir);*/

}
