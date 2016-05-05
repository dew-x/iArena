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
	while (true) {
		sf::Socket::Status s = socket.receive(in, sizeof(in), received, sender, senderPort);
		if (received != 0) {
			Message got = Protocol::decode(in);
			if (got.t < Message::MAX) {
				string UUID = (string)sender.toString() + to_string(senderPort);
				if (got.t == Message::REQUEST_LOGIN) {
					users[UUID] = { sender,senderPort,got.ts,got.As.rLogin.nick,cuid,0.0f,0.0f };
					++cuid;
				}
				if (users.count(UUID)>0) {
					User u = users[UUID];
					Message res = u.message(got);
					if (res.t != Message::NONE) socket.send(Protocol::encode(res), sizeof(Message) , u.ip, u.port);
				}
			}
		}
	}
}
