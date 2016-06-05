#include "Server.h"



Server::Server(unsigned port)
{
	this->port = port;
}


Server::~Server()
{
}

void Server::run()
{
	int cuid = 0;
	if (socket.bind(port) != sf::Socket::Done) {
		cout << "Coudn't start server: bind failed" << endl;
		return;
	}
	cout << "Server is listening to port " << port << endl;
	cout << "Protocol message size: " << sizeof(Message) << endl;
	socket.setBlocking(false);
	char in[sizeof(Message)];
	memset(in, '\0', sizeof(Message));
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	sf::Clock clock;
	int previous = clock.getElapsedTime().asMilliseconds();
	while (true) {
		sf::Socket::Status s = socket.receive(in, sizeof(in), received, sender, senderPort);
		if (received != 0) {
			Message got = Protocol::decode(in);
			if (got.t < Message::MAX) {
				string UUID = (string)sender.toString() + to_string(senderPort);
				if (got.t == Message::REQUEST_LOGIN) {
					User newUser;
					newUser.dir = { 0.0f,0.0f };
					newUser.ip = sender;
					newUser.nick = got.As.rLogin.nick;
					newUser.port = senderPort;
					newUser.ts = got.ts;
					newUser.uid = cuid;
					newUser.position = { 1000.0f,1000.0f };
					newUser.hp = 100;
					newUser.last = (int)got.uid-1;
					users[UUID] = newUser;
					entities[cuid] = &users[UUID];
					++cuid;
					cout << "Current users: " << cuid << endl;
					// broadcast login
					broadcast(UUID,Protocol::spawn(1000.0f, 1000.0f, newUser.uid, got.As.rLogin.nick, newUser.hp));
				}
				if (users.count(UUID)>0) {
					User *u = &users[UUID];
					Message tobroadcast=Protocol::make(Message::NONE);
					Message res = u->message(got,entities, tobroadcast);
					if (tobroadcast.t!=Message::NONE) broadcast(UUID, tobroadcast);
					if (res.t != Message::NONE) socket.send(Protocol::encode(res), sizeof(Message) , u->ip, u->port);
				}
			}
		}
		int current = clock.getElapsedTime().asMilliseconds();
		if (current != previous) {
			int steps = current - previous;
			for (int s = 0; s < steps; ++s) {
				for (auto it = users.begin(); it != users.end(); ++it) {
					it->second.update();
				}
			}
			previous = current;
		}
	}
}

void Server::broadcast(string UUID, const Message &m)
{
	const char *data = Protocol::encode(m);
	for (auto it = users.begin(); it != users.end(); ++it) {
		if (it->first != UUID) {
			socket.send(data, sizeof(Message), it->second.ip, it->second.port);
		}
	}
}
