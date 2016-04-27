#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
using namespace std;

int main() {
	cout << "OK" << endl;
	sf::UdpSocket a;
	a.bind(5000);
}