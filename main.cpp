#define VERSION 1

#if VERSION == 1
//This is the latest version of BeagleBone server - it accepts a client connection and passes information through
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <iostream>

//BB-UART Serial Information
#define PORT "/dev/ttyO4"
#define BAUDRATE B115200
int ClientConnected = -1;
struct PktDef
{
	unsigned Forward : 1;
	unsigned Backwards : 1;
	unsigned Left : 1;
	unsigned Right : 1;
	unsigned ArmUp : 1;
	unsigned ArmDn : 1;
	unsigned GripO : 1;
	unsigned GripC : 1;
};
//Buffers
char read_buffer[1];
char write_buffer[1];
char sendBuff[1];
char recvBuff[1];
//PktDef ThePacket[1];
//PktDef& packPacket(char Direction, char Action) 
//{

//}
void RxBytes(int &uart, void *buffer, size_t MaxSize) {
	if (uart != -1) {
		int rx_length = read(uart, buffer, MaxSize);

		if (rx_length == 0) {
			std::cout << "ERROR Reading UART\n" << std::endl;
		}
	}
}

void TxBytes(int &uart, void *buffer, size_t MaxSize)
{
	if (uart != -1)
	{
		int count = write(uart, buffer, MaxSize);
		if (count < 0)
		{
			std::cout << "ERROR writing to UART" << std::endl;
		}
	}

}

int main(void) {
	int uart_stream = -1;
	int welcomeSocket = 0;
	int connectionSocket = 0;
	struct sockaddr_in serv_addr;
	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(read_buffer, '0', sizeof(read_buffer));
	memset(write_buffer, '0', sizeof(write_buffer));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);

	uart_stream = open(PORT, O_RDWR);
	if (uart_stream == -1)
	{
		std::cout << "Failed to open BB-UART" << std::endl;
		getchar();
		return(-1);
	}
	std::cout << "BB-UART Opened" << std::endl;

	//Configure BB-UART
	struct termios options;
	tcgetattr(uart_stream, &options);
	options.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;//sets baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VMIN] = 1; //size of packet
	options.c_cc[VTIME] = 0;
	tcflush(uart_stream, TCIFLUSH);
	tcsetattr(uart_stream, TCSANOW, &options);
	//Listen for connections
	bind(welcomeSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	listen(welcomeSocket, 10);
	std::cout << "Listening for a connection" << std::endl;
	//if client is connected
	while (true)//awaiting connection;
	{
		connectionSocket = accept(welcomeSocket, (sockaddr*)NULL, NULL);
		if (connectionSocket == -1) //this flag changes depending on accepted connections
		{
			sleep(5);
			std::cout << "Awaiting Connection" << std::endl;
		}
		else
		{
			std::cout << "Client Connected" << std::endl;
			while (uart_stream != -1)
			{
				//RxBytes(uart_stream, read_buffer, sizeof(read_buffer));
				//std::cout << read_buffer << std::endl;
				RxBytes(connectionSocket, read_buffer, sizeof(read_buffer));
				std::cout << "Message = " << read_buffer << std::endl;

				//read(connectionSocket, write_buffer, sizeof(write_buffer));
				//std::cout << "Reading from client" << write_buffer << std::endl;
				//TxBytes(uart_stream, write_buffer, sizeof(write_buffer));

//				RxBytes(uart_stream, read_buffer, sizeof(read_buffer));
//				write(connectionSocket, read_buffer, sizeof(read_buffer));
//				std::cout << "Reading from Robot" << read_buffer << std::endl;

				memset(read_buffer, '0', sizeof(read_buffer));
				//memset(write_buffer, '0', sizeof(write_buffer));

//				read(connectionSocket, write_buffer, sizeof(write_buffer));
//				std::cout << "Wwrite buff " << write_buffer << std::endl;
//				TxBytes(uart_stream, write_buffer, sizeof(write_buffer));


			//	RxBytes(uart_stream, read_buffer, sizeof(read_buffer));
			//	std::cout << read_buffer << std::endl;
			//	write(connectionSocket, read_buffer, sizeof(read_buffer));

				//memset(read_buffer, '0', sizeof(read_buffer));
				//memset(write_buffer, '0', sizeof(write_buffer));

				//std::cin >> write_buffer;

			}
		}
	}
	getchar();
	getchar();
}
#endif
#if VERSION == 0
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <iostream>

//BB-UART Serial Information
#define PORT "/dev/ttyO4"
#define BAUDRATE B115200
int ClientConnected = -1;
struct PktDef
{
	unsigned Forward : 1;
	unsigned Backwards : 1;
	unsigned Left : 1;
	unsigned Right : 1;
	unsigned ArmUp : 1;
	unsigned ArmDn : 1;
	unsigned GripO : 1;
	unsigned GripC : 1;
};
//Buffers
char read_buffer[1];
char write_buffer[1];
char sendBuff[1];
char recvBuff[1];
//PktDef ThePacket[1];
//PktDef& packPacket(char Direction, char Action) 
//{
	
//}
void RxBytes(int &uart, void *buffer, size_t MaxSize) {
	if (uart != -1) {
		int rx_length = read(uart, buffer, MaxSize);

		if (rx_length == 0) {
			std::cout << "ERROR Reading UART\n" << std::endl;
		}
	}
}

void TxBytes(int &uart, void *buffer, size_t MaxSize)
{
	if (uart != -1)
	{
		int count = write(uart, buffer, MaxSize);
		if (count < 0)
		{
			std::cout << "ERROR writing to UART" << std::endl;
		}
	}

}

int main(void) {
	int uart_stream = -1;
	int welcomeSocket = 0;
	int connectionSocket = 0;
	struct sockaddr_in serv_addr;
	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);

	uart_stream = open(PORT, O_RDWR);
	if (uart_stream == -1)
	{
		std::cout << "Failed to open BB-UART" << std::endl;
		getchar();
		return(-1);
	}
	std::cout << "BB-UART Opened" << std::endl;

	//Configure BB-UART
	struct termios options;
	tcgetattr(uart_stream, &options);
	options.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;//sets baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VMIN] = 1; //size of packet
	options.c_cc[VTIME] = 0;
	tcflush(uart_stream, TCIFLUSH);
	tcsetattr(uart_stream, TCSANOW, &options);
	//Listen for connections
	bind(welcomeSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	listen(welcomeSocket, 10);
	std::cout << "Listening for a connection" << std::endl;
	//if client is connected
	while (true)//awaiting connection;
	{
		connectionSocket = accept(welcomeSocket, (sockaddr*)NULL, NULL);
		if (connectionSocket == -1) //this flag changes depending on accepted connections
		{
			sleep(5);
			std::cout << "Awaiting Connection" << std::endl;
		}
		else 
		{
			std::cout << "Client Connected" << std::endl;
			while (uart_stream != -1)
			{
				RxBytes(uart_stream, read_buffer, sizeof(read_buffer));
				std::cout << read_buffer << std::endl;
				read(connectionSocket, write_buffer, sizeof(write_buffer));
				write(connectionSocket, read_buffer, sizeof(read_buffer));
				TxBytes(uart_stream, write_buffer, sizeof(write_buffer));
			}
		}
	}
	getchar();
	getchar();
}

#endif