#include <windows.networking.sockets.h>
#include <stdio.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

void main(int argc, char *argv[])
{
	unsigned int pktCount = 0;
	struct sockaddr_in SvrAddr;
	SOCKET ClientSocket;
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 3);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		return;

	if ((ClientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return;

	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_port = htons(5000);
	SvrAddr.sin_addr.s_addr = inet_addr("192.168.8.1");

	//Connect socket to specified server
	if ((connect(ClientSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR)
	{
		closesocket(ClientSocket);
		WSACleanup();
		cout << " No connection to server" << endl;
		return;
	}
	char TxBuffer[1];


	while (1)
	{
		cout << "Robot input (! for menu) \n";
		cin >> TxBuffer;
		if (TxBuffer[0] != '!') {
			send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);
		}
		else {
			cout << " 'w' - Forward\n 's' - Backwards\n 'a' - Left\n 'd' - Right\n 't' - Arm up\n 'y' - Arm down\n 'g' - Open grip\n 'h' - Close grip\n " << endl;
		}

	}

	closesocket(ClientSocket);
	WSACleanup();
}
