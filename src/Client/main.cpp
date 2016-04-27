#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "const.h"
using namespace std;

int main() {
	// Ask for the server address
	sf::IpAddress server = "localhost";

	// Create a socket for communicating with the server
	sf::UdpSocket socket;

	// Send a message to the server
	const char out[] = "Hi, I'm a client";
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