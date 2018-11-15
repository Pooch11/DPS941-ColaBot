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

int main(int argc, char *argv[])
{
	int sockfd = 0, n = 0;
	char recvBuff[1024];
	struct sockaddr_in client_addr;

	if (argc > 5)
	{
		std::cout << "\n Usage: %s 192.168.8.1 \n" << argv[0] << std::endl;
		std::cin.get();
		std::cin.get();
		return 1;
	}

	memset(recvBuff, '0', sizeof(recvBuff));
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

	while ((n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0)
	{
		recvBuff[n] = 0;
		if (fputs(recvBuff, stdout) == EOF)
		{
			std::cout << " Error : Fputs error" << std::endl;
			std::cin.get();
			std::cin.get();
		}
	}

	if (n < 0)
	{
		printf("\n Read error \n");
	}
	std::cout << "Connection established" << std::endl;
	std::cin.get();
	std::cin.get();
	return 0;
}