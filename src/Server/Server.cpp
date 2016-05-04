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
	while (true) {
		sf::Socket::Status s = socket.receive(in, sizeof(in), received, sender, senderPort);
		if (received != 0) {
			Message got = Protocol::decode(in);
			if (got.t < Message::MAX) {
				string UUID = (string)sender.toString() + to_string(senderPort);
				if (got.t == Message::REQUEST_LOGIN) {
					users[UUID] = User(sender,senderPort,got.ts,got.As.rLogin.nick);
				}
				else {
					iter pos = users.find(UUID);
					if (pos != users.end()) {
						users[UUID].message(&socket, got);
					}
				}
			}
		}
	}
}
