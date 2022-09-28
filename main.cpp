#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
using namespace std;

class X
{
	int a;
public:
	X() { cout << "X()" << endl; }
	~X() { cout << "~X()" << endl; }
	void func() {}
};

class Y
{
	int b;
public:
	Y() { cout << "Y()" << endl; throw 1; }
	~Y() { cout << "~Y()" << endl; }
	void func() {}
};

bool func() {
	cout << "func()\n";
	return 1;
}

void func2() {
	cout << "func2()\n";
}

void func3(X* x) {
	cout << "func3()\n";
}

void func4(std::unique_ptr<X> a, std::unique_ptr<Y> b) {
	cout << "func4()\n";
	throw 1;
}

void func5(X* x, Y* y) {
	cout << "func5()\n";
}

void func7(std::unique_ptr<X> a) {
	cout << "func7()\n";
}

int main()
{
	{
		std::shared_ptr<X> ptr = std::make_shared<X>();
		cout << ptr.use_count() << endl;
		{
			std::shared_ptr<X> ptr2 = ptr;	
			cout << ptr.use_count() << endl;
		}
		cout << ptr.use_count() << endl;
		ptr.reset();
		cout << ptr.use_count() << endl;
	}

	return 0;

	func4(std::unique_ptr<X>(new X()), std::unique_ptr<Y>(new Y()));
	//func4(std::make_unique<X>(), std::make_unique<Y>());
	return 0;

	{
		std::unique_ptr<X> object1(new X());  // Избавились от операции delete
		auto object2 = std::make_unique<X>();  // Избавились от операции new
		//func3(object2.get());
		cout << '.';
		throw 1;
	}
	return 0;

	//X* object1 = new X();
	if (func()) {
		func2();
		return 1;
	}
	//delete object1;
	cout << ".\n";

	return 0;


	sf::TcpSocket socket;
	cout << "connect";
	while (true)
	{
		sf::Socket::Status status = socket.connect("192.168.88.200", 55001);

		if (status == sf::Socket::Done)
		{
			cout << "done" << endl;
			break;
		}
		else { cout << '.'; }
	}

	while (true)
	{
		std::string str;
		// 0. Создаём пакет
		sf::Packet packet;
		// 1. Зададим код пакета
		sf::Uint32 pack_type;
		cin >> pack_type;
		// 2. засунем его в пакет
		packet << pack_type;

		// Отправка своего имени серверу
		if (pack_type == 3)
		{
			cin >> str;
			packet << str;
		}

		// Отправка текстового сообщения на сервер
		else if (pack_type == 4)
		{
			getline(cin, str, ';');
			packet << str;
		}
		// Отправка координат на сервер
		else if (pack_type == 5)
		{
			float x, y;
			cin >> x >> y;
			packet << x << y;
		}

		socket.send(packet);

		sf::Packet packet2;
		socket.receive(packet2);
		string str2;
		packet2 >> str2;
		cout << str2;

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