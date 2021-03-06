#include "Game.h"



Game::Game()
{
	width = 800;
	height = 600;
	/*width = sf::VideoMode::getDesktopMode().width;
	height = sf::VideoMode::getDesktopMode().height;
	app.create(sf::VideoMode::getDesktopMode(), "GAME", sf::Style::Fullscreen);*/
	app.create(sf::VideoMode(width, height), "GAME", sf::Style::Default);
	app.setVerticalSyncEnabled(true);
	app.setKeyRepeatEnabled(false);
	scene = SCENE_LOGIN;
	nickpos = 0;
	memset(nick, 0, NICKSIZE);
	font = sf::Font();
	font.loadFromFile("madpixels.otf");
	typeYourNick = sf::Text("Type your nick:", font, height / 30);
	typeYourNick.setOrigin({ typeYourNick.getLocalBounds().width / 2.0f,typeYourNick.getLocalBounds().height / 2.0f });
	typeYourNick.setPosition({ width / 2.0f,height / 2.2f });
	typeYourNick.setColor(sf::Color::Red);
	fpsText = sf::Text("FPS:", font, height / 30);
	fpsText.setColor(sf::Color::Red);
	uid = -1;
	C = NULL;
	P = NULL;
	M = NULL;
	orders = vector<Message>(0);
	projectiles = vector<Projectile>(0);
	enemies = vector<Enemy*>(0);
	deltaClock = sf::Clock();
	projectileID = 0;
	fps = 0;

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

	if (!p.loadFromFile("textures/fireBall2.png"))
	{
		// error...
	}

	texEnemy.loadFromFile("textures/player.gif");
	
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

	while (enemies.size()) {
		delete enemies[enemies.size() - 1];
		enemies.pop_back();
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
				if (scene == SCENE_GAME) {
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						//sf::Vector2f d = { sf::Mouse::getPosition().x - (width / 2.0f) , sf::Mouse::getPosition().y - (height / 2.0f) };
						sf::Vector2f d = { event.mouseButton.x - (width / 2.0f) , event.mouseButton.y - (height / 2.0f) };
						d = normalize(d);
						Message m = Protocol::fireWeapon(d.x, d.y, projectileID);
						C->send(m);
						orders.push_back(m);
						saveState();
						Projectile projectile;
						projectileID++;
						projectiles.push_back(projectile);
						projectiles[projectiles.size() - 1].init(P->getPosition(), d, (1920*PLAYERSIZE) / 5, projectileID, p);
					}
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
		fps = 0.99f*fps + 0.01f / dt.asSeconds();
		fpsText.setString(to_string((int)fps) + " FPS");
		app.draw(fpsText);
		app.display();
		
	}
}

void Game::commitNick()
{
	scene = SCENE_LOADING;
	C = new Comm(SERVERIP);
	T = thread(&Comm::init, C);
	Message m = Protocol::rLogin(nick);
	if (!C->send(m)) {
		orders.push_back(m);
		saveState();
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
				P = new Player(m.As.Login.uid, m.As.Login.x, m.As.Login.y, 1920*PLAYERSIZE,nick,font,m.As.Login.hp);
				M = new Map();
				for (int i = 0; i < m.As.Login.entityCount; ++i) {
					Enemy * e = new Enemy(m.As.Login.entities[i].id, m.As.Login.entities[i].x, m.As.Login.entities[i].y, m.As.Login.entities[i].name, texEnemy, 1920*PLAYERSIZE,font, m.As.Login.entities[i].hp);
					e->setEncodedDirection(m.As.Login.entities[i].direction);
					enemies.push_back(e);
				}
				for (int i = 0; i < m.As.Login.itemCount; ++i) {
					cout << m.As.Login.items[i].type << " " << m.As.Login.items[i].x << " " << m.As.Login.items[i].y << " thats all " << endl;
				}
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
	float radians = atan2(sf::Mouse::getPosition(app).y - height / 2.0f, sf::Mouse::getPosition(app).x - width / 2.0f);
	//float radians = atan2(sf::Mouse::getPosition().y - height / 2.0f, sf::Mouse::getPosition().x - width / 2.0f);
	P->setRotation(RadToDeg(radians));

	for (unsigned i = 0; i < projectiles.size(); i++) {
		projectiles[i].updatePos((float)dt.asMilliseconds());
	}

	for (unsigned i = 0; i < enemies.size(); i++) {
		enemies[i]->update((float)dt.asMilliseconds());
	}

	scope.setPosition((float)sf::Mouse::getPosition(app).x,(float) sf::Mouse::getPosition(app).y);
	//scope.setPosition((float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y);
	while (!C->empty()) {
		Message m = C->poll();
		if (m.ack != -1 && (unsigned)m.ack<orders.size() && orders[m.ack].ts+1000<Protocol::now()) {
			printf("DESYNC: ACK: %d ORDERS: %d LAST: %d NOW: %d", m.ack, orders.size(), orders[m.ack].ts, Protocol::now());
			// rollback to ack
			while (orders.size() > (unsigned)m.ack) {
				orders.pop_back();
			}
			while ((unsigned)projectileID > states[m.ack].pcount) {
				--projectileID;
				projectiles.pop_back();
			}
			P->setState(states[m.ack]);
		}
		Enemy *e;
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
 					P->rectificateA((float)delta,dir);
					P->setTarget(m.As.nKeys.x, m.As.nKeys.y);
				}
			}
			break;
		case Message::FIRE_WEAPON:
			break;
		case Message::FIRE_RESULT:
			for (unsigned j = 0; (int)j < m.As.rFire.size; ++j) {
				for (unsigned k = 0; k < enemies.size(); ++k) {
					if (m.As.rFire.hits[j].uid == enemies[k]->getID()) {
						enemies[k]->dealDamage(m.As.rFire.hits[j].damage);
					}
				}
			}
			break;
		case Message::FIRE_BROADCAST:
			for (unsigned i = 0; i < enemies.size(); ++i) {
				if (enemies[i]->getID() == m.As.bFire.uid) {
					// make new projectyle
					Projectile projectile;
					projectileID++;
					projectiles.push_back(projectile);
					projectiles[projectiles.size() - 1].init(enemies[i]->getPosition(), { m.As.bFire.x,m.As.bFire.y }, (1920 * PLAYERSIZE) / 5, projectileID, p);
					for (unsigned j = 0; (int)j < m.As.bFire.size; ++j) {
						if (m.As.bFire.hits[j].uid == P->getUID()) {
							P->dealDamage(m.As.bFire.hits[j].damage);
						}
						else {
							for (unsigned k = 0; k < enemies.size(); ++k) {
								if (m.As.bFire.hits[j].uid == enemies[k]->getID()) {
									enemies[k]->dealDamage(m.As.bFire.hits[j].damage);
								}
							}
						}
					}
				}
			}
			break;
		case Message::SPAWN:
			e=new Enemy(m.As.spawn.id, m.As.spawn.x, m.As.spawn.y, m.As.spawn.name, texEnemy, 1920.0f*PLAYERSIZE,font,m.As.spawn.hp);
			enemies.push_back(e);
			break;
		case Message::SPAWN_ITEM:
			cout << m.As.sItem.type << " " << m.As.sItem.x << " " << m.As.sItem.y << "thats all" << endl;
			break;
		case Message::UPDATE_STATE:
			for (unsigned i = 0; i < enemies.size(); ++i) {
				if (enemies[i]->getID() == m.As.uState.data.id) {
					enemies[i]->updateState(m.As.uState.data);
				}
			}
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
	view.zoom(1920.0f/width);
	app.setView(view);
	app.draw(*M);
	app.draw(*P);
	// draw enemies
	for (unsigned i = 0; i < enemies.size(); i++) {
		app.draw(*enemies[i]);
	}
	for (unsigned i = 0; i < projectiles.size(); i++) {
		app.draw(projectiles[i]);
	}

	

	//draw other players
	app.setView(app.getDefaultView());

	app.draw(scope);

}

void Game::updateMovement() {

	Message m = Protocol::uKeys(
		sf::Keyboard::isKeyPressed(sf::Keyboard::W), 
		sf::Keyboard::isKeyPressed(sf::Keyboard::A), 
		sf::Keyboard::isKeyPressed(sf::Keyboard::S), 
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)
	);
	C->send(m);
	orders.push_back(m);
	saveState();
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
	P->setAcceleration(dir);
}

void Game::saveState()
{
	State s;
	s.pcount = projectileID;
	s.acceleration = P->getAcceleration();
	s.direction = P->getDirection();
	s.position = P->getPosition();
	s.V0 = P->getV0();
	s.velocity = P->getVelocity();
	states.push_back(s);
}
