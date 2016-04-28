#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "const.h"
#include <string>
#include <PROTO\Protocol.h>
#include "Game.h"
using namespace std;

int main() {
	// Ask for the server address
	sf::IpAddress server = "localhost";

	// Create a socket for communicating with the server
	sf::UdpSocket socket;

	// Send a message to the server
	Message req = Protocol::rLogin("DEW");
	const char *what = Protocol::encode(req);
	if (socket.send(what, sizeof(Message), server, port) != sf::Socket::Done) {
		cout << "Can't connect to server" << endl;
		return 1;
	}

	// Receive an answer from anyone (but most likely from the server)
	char in[BUFSIZE];
	memset(in, '\0', BUFSIZE);
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	sf::Socket::Status s = socket.receive(in, sizeof(in), received, sender, senderPort);
	if (s != sf::Socket::Done) {
		cout << "Socket recieve failed" << endl;
		return 1;
	}
	Message res = Protocol::decode(in);
	std::string buff = in;
	cout << s << " " << buff << " " << received << " " << sender << " " << senderPort << endl;
	cout << res.t << " " << res.ts << " " << res.As.Login.uid << " " << res.As.Login.x <<" "<< res.As.Login.y << endl;
	Game g;
	g.run();
	return 0;
}