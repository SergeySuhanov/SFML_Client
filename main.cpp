#include <SFML/Network.hpp>
#include <iostream>
using namespace std;

int main()
{
	sf::TcpSocket socket;
	cout << "connect";
	while (true)
	{
		sf::Socket::Status status = socket.connect("192.168.88.209", 55001);

		if (status == sf::Socket::Done)
		{
			cout << "done" << endl;
			break;
		}
		else { cout << '.'; }
	}

	sf::Packet packet;
	packet << "Hello server!";
	socket.send(packet);

	sf::Packet packet2;
	socket.receive(packet2);
	string str;
	packet2 >> str;
	cout << str;

	return 0;
}