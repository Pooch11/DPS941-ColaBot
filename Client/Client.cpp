#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <iostream>
int EstablishConnection(sockaddr_in client_addr);

int main(int argc, char *argv[])
{
	char recvBuff[1];
	char sendBuff[1];
	int sockfd = 0;
	struct sockaddr_in client_addr;

	memset(recvBuff, '0', sizeof(recvBuff));
	memset(sendBuff, 'A', sizeof(sendBuff));
	
	sockfd = EstablishConnection(client_addr);

	while (sockfd != -1) {
		std::cout << "Enter a command" << std::endl;
		std::cin >> sendBuff;
		write(sockfd, sendBuff, sizeof(sendBuff));
		memset(sendBuff, '0', sizeof(sendBuff));

		read(sockfd, recvBuff, sizeof(recvBuff));
		std::cout << "You received this message: " << std::endl;
		std::cout << recvBuff << std::endl;
		memset(recvBuff, '0', sizeof(recvBuff));
	}


	
	
	std::cerr << recvBuff << std::endl;
	std::cin.get();
	std::cin.get();
	return 0;
}

int EstablishConnection(sockaddr_in client_addr) {
	int sockfd = 0;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "Error : Could not create socket" << std::endl;
		std::cin.get();
		std::cin.get();
		return 1;
	}

	memset(&client_addr, '0', sizeof(client_addr));

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(5000);

	if (inet_pton(AF_INET, "192.168.8.1", &client_addr.sin_addr) <= 0)
	{
		std::cout << "error occured" << std::endl;
		std::cin.get();
		std::cin.get();
		return 1;
	}
	if (connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
	{
		std::cout << "Error : Connect Failed \n" << std::endl;
		std::cin.get();
		std::cin.get();
		return 1;
	}
	std::cout << "Connection established" << std::endl;
	return sockfd;
}

