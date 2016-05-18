#include "Comm.h"



Comm::Comm(sf::IpAddress server)
{
	this->server = server;
	end = false;
}


Comm::~Comm()
{
}

void Comm::init()
{
	socket.setBlocking(false);
	char in[sizeof(Message)];
	memset(in, '\0', sizeof(Message));
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	while (!end) {
		sf::Socket::Status s = socket.receive(in, sizeof(in), received, sender, senderPort);
		if (received > 0) {
			if (s != sf::Socket::Done) {
				end = true;
			}
			else {
				int pos = queue.size() - 1;
				Message m = Protocol::decode(in);
				// check if message is valid
				if (m.t<Message::MAX) {
					std::string buff = in;
					/*cout << s << " " << buff << " " << received << " " << sender << " " << senderPort << endl;
					cout << m.t << " " << m.ts << " " << m.As.Login.uid << " " << m.As.Login.x << " " << m.As.Login.y << endl;*/
					queue.push_back(m);
					// sort to proper order
					while (pos >= 0 && queue[pos].ts > queue[pos + 1].ts) {
						swap(queue[pos + 1], queue[pos]);
						--pos;
					}
				}
			}
		}
	}
}

bool Comm::empty()
{
	return queue.size()==0;
}

Message Comm::poll()
{
	Message ret = queue[0];
	queue.erase(queue.begin(), queue.begin() + 1);
	return ret;
}

bool Comm::send(Message m)
{
	const char *what = Protocol::encode(m);
	if (socket.send(what, sizeof(Message), server, port) != sf::Socket::Done) {
		return false;
	}
	return true;
}

void Comm::stop()
{
	end = true;
}
