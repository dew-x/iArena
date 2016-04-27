#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "const.h"
#include <string>
#include "Protocol.h"
using namespace std;

int main() {
	// Ask for the server address
	sf::IpAddress server = "localhost";

	// Create a socket for communicating with the server
	sf::UdpSocket socket;

	// Send a message to the server

	const char out[] = "Hi, I'm a client";
	Message req = Protocol::rLogin("DEW");
	cout << req.t << " " << req.ts << endl;
	cout << req.As.rLogin.nick << endl;
	//con
	const char *what = Protocol::encode(req);
	for (unsigned i = 0; i < sizeof(Message); ++i) cout <<i<<" "<< what[i]<<endl;
	cout << endl;
	Message req2 = Protocol::decode(what);
	cout << req2.t << " " << req2.ts << endl;
	cout << req2.As.rLogin.nick << endl;
	if (socket.send(out, sizeof(out), server, port) != sf::Socket::Done) {
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
	string buff = in;
	cout << s << " " << buff << " " << received << " " << sender << " " << senderPort << endl;
	return 0;
}