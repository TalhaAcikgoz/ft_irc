#include "ft_irc.hpp"

int connect_socket(int sockett) {
	int connectt;

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Sunucu IP adresi
	serverAddress.sin_port = htons(4242); // Sunucu bağlantı noktası

	// Sokete bağlanma
	if ((connectt = connect(sockett, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress))) == -1) {
		std::cerr << "Sokete bağlanılamadı." << std::endl;
		return -1;
	}
	return connectt;
}

int main() {
	int bindd;
	int listenn;
	int socketwo = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (socketwo == -1)
		std::cerr << "socketwo is not opened" << std::endl;
	else
		std::cout << "socketwo fd:" << socketwo << std::endl;

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(4242);

	if ((bindd = bind(socketwo, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress))) == -1) {
		std::cerr << "socket baglanamadi." << std::endl;
		return 1;
	}

	if ((listenn = listen(socketwo, 1)) == -1) {
		std::cerr << "socket dinleme hatali." << std::endl;
		return 1;
	}

	std::cout << "bind: " << bindd << " listenn: " << listenn << std::endl << "socket dinlenmeye baslandi." << std::endl;

	std::cout << "connect: " << connect_socket(socketwo) << std::endl;

	while (1) {
		;
	}

	return 0;
}
