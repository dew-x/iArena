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
					users[UUID] = newUser;
					entities[cuid] = &users[UUID];
					++cuid;
					cout << "Current users: " << cuid << endl;
				}
				if (users.count(UUID)>0) {
					User *u = &users[UUID];
					Message res = u->message(got,entities);
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
