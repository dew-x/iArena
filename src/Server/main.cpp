#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "const.h"
#include <string>
using namespace std;

int main() {
	// Create a socket to receive a message from anyone
	sf::UdpSocket socket;

	// Listen to messages on the specified port
	if (socket.bind(port) != sf::Socket::Done) {
		cout << "Coudn't start server: bind failed" << endl;
		return 1;
	}

	std::cout << "Server is listening to port " << port << std::endl;
	socket.setBlocking(false);
	char in[BUFSIZE];
	memset(in, '\0', BUFSIZE);
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	while (true) {
		sf::Socket::Status s = socket.receive(in, sizeof(in), received, sender, senderPort);
		if (received != 0) {
			string buff = in;
			cout << s << " " << buff << " " << received << " " << sender << " " << senderPort << endl;
			const char out[] = "Hi, I'm the server";
			if (socket.send(out, sizeof(out), sender, senderPort) != sf::Socket::Done)
				return 1;
		}
	}
	return 0;
}