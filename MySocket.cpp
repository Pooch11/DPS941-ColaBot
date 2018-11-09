#include "MySocket.h"

MySocket::MySocket(SocketType socktype, std::string ip, unsigned int prt, ConnectionType contype, unsigned int size) {
	ConnectionSocket = SOCKET_ERROR;
	WelcomeSocket = SOCKET_ERROR;							//initilize sockets to SOCKET_ERROR for validation
	bTCPConnect = false;
	SetType(socktype);
	connectionType = contype;								//set the socket and connection types

	SetIPAddr(ip);
	setPort(prt);
	Buffer = (size > 0 && size < DEFAULT_SIZE) ? new char[size] : new char[DEFAULT_SIZE];
	//set the ip address and port. Allocate data for buffer.
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = inet_addr(IPAddr.c_str());
	SvrAddr.sin_port = htons(prt);									//initialize sockaddr_in object

	WSADATA wsaData;															//start DLLs
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return;
	}

	if (mySocket == CLIENT) {			//FOR CLIENT CONNECTIONS:
		if (connectionType == TCP) {											//TCP
			if (connectSocket(ConnectionSocket, SOCK_STREAM, IPPROTO_TCP)) {	//initilize connection socket for a TCP connection
				std::cout << "Initializing client Socket" << std::endl;
			}
		}
		else if (connectionType == UDP) {										//UDP
			connectSocket(ConnectionSocket, SOCK_DGRAM, IPPROTO_UDP);			//initilize connection socket for a UDP connection
			std::cout << "Initilizing client Socket" << std::endl;
		}
	}																			/**************************************************/
	else if (mySocket == SERVER) {		//FOR SERVER CONNECTIONS:
		if (connectionType == TCP) {											//TCP
			if (connectSocket(WelcomeSocket, SOCK_STREAM, IPPROTO_TCP)) {		//initilize and bind welcome socket for a TCP connection

				if (listen(WelcomeSocket, 1) == SOCKET_ERROR) {					//Listen on server socket
					closesocket(WelcomeSocket);
					WSACleanup();
					return;
				}
				std::cout << "Waiting for client connection... " << std::endl;

				ConnectTCP();													//Accept
			}
		}
		else if (connectionType == UDP) {										//UDP
			connectSocket(ConnectionSocket, SOCK_DGRAM, IPPROTO_UDP);			//Initilize and bind welcome socket for a UDP connection
			std::cout << "Initilizing server Socket" << std::endl;
		}
	}
}

bool MySocket::connectSocket(SOCKET& s, int type, int protocol) {
	s = socket(AF_INET, type, protocol);										//Initialize the socket
	if (s == INVALID_SOCKET) {
		WSACleanup();
		std::cout << "Could not initialize socket" << std::endl;
		return false;
	}
	if (mySocket == SERVER) {
		if (bind(s, (struct sockaddr*) &SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR) {//Bind server socket
			closesocket(s);
			WSACleanup();
			return false;
		}
	}

	return true;
}

MySocket::~MySocket() {

	DisconnectTCP();										// closes welcome and connection Sockets for TCP connections
	if (connectionType == UDP) {
		closesocket(ConnectionSocket);						// closes connection Sockets for UDP connections
	}
	WSACleanup();											// closes DLL for any type of connection
	delete[] Buffer;
}


void MySocket::ConnectTCP() {
	if (mySocket == CLIENT && connectionType == TCP) {
		if ((connect(ConnectionSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
			closesocket(ConnectionSocket);										//connects socket for TCP client
			WSACleanup();
			std::cout << "Unable to connect with Server" << std::endl;
		}
		else {
			std::cout << "Connection Established with Server" << std::endl;
			bTCPConnect = true;
		}
	}
	else if (mySocket == SERVER && connectionType == TCP) {
		if ((ConnectionSocket = accept(WelcomeSocket, NULL, NULL)) == SOCKET_ERROR) {
			closesocket(WelcomeSocket);											//accepts connection on tcp server welcomeSocket
			WSACleanup();
		}
		else {
			std::cout << "Connection Accepted with Client" << std::endl;
			bTCPConnect = true;
		}
	}
}

void MySocket::DisconnectTCP() {												//Disconnects TCP sockets
	bTCPConnect = false;
	if (connectionType == TCP) {
		if (mySocket == SERVER) {
			closesocket(ConnectionSocket);
			closesocket(WelcomeSocket);
		}
		else {
			closesocket(ConnectionSocket);
		}
	}
}

void MySocket::SendData(const char* data, int bytes) {
	if (connectionType == TCP) {											//sends data for TCP connection
		send(ConnectionSocket, data, bytes, 0);
	}
	else if (connectionType == UDP) {										//sends data for UDP connection
		sendto(ConnectionSocket, data, bytes, 0, (sockaddr *)&SvrAddr, sizeof(SvrAddr));
	}
}

int MySocket::GetData(char* buffer) {
	int returnvalue = 0;
	if (connectionType == TCP) {											//receives data for TCP connections
		returnvalue = recv(ConnectionSocket, Buffer, DEFAULT_SIZE, 0);
		if (returnvalue == SOCKET_ERROR) {
			return WSAGetLastError();
		}
	}
	else if (connectionType == UDP) {										//receives data for UDP connections
		sockaddr_in CltAddr;												/** This does not allow UDP to send messages back to same person **/
		int addr_len = sizeof(CltAddr);
		returnvalue = recvfrom(ConnectionSocket, Buffer, DEFAULT_SIZE, 0, (sockaddr *)&CltAddr, &addr_len);
		if (returnvalue == SOCKET_ERROR) {
			return WSAGetLastError();
		}
	}
	memcpy(buffer, Buffer, returnvalue);
	return returnvalue;
}

std::string MySocket::GetIPAddr() {		//get IP
	return IPAddr;
}

void MySocket::SetIPAddr(std::string ip) {
	if (ConnectionSocket == SOCKET_ERROR && WelcomeSocket == SOCKET_ERROR) { //only sets IP if there is no connection
		IPAddr = ip;
	}
	else {
		std::cout << "CONNECTION ALREADY ESTABLISHED!!" << std::endl;
	}
}

void MySocket::setPort(unsigned int p) {
	if (ConnectionSocket == SOCKET_ERROR && WelcomeSocket == SOCKET_ERROR) { //only sets port if there is no connection
		port = p;
	}
	else {
		std::cout << "CONNECTION ALREADY ESTABLISHED!!" << std::endl;
	}
}

int MySocket::getPort() {			//get port
	return port;
}

SocketType MySocket::GetType() {	//get socket type
	return mySocket;
}

void MySocket::SetType(SocketType type) {
	if (ConnectionSocket == SOCKET_ERROR && WelcomeSocket == SOCKET_ERROR) { //only sets connection type if there is no connection
		mySocket = type;
	}
	else {
		std::cout << "CONNECTION ALREADY ESTABLISHED!!" << std::endl;
	}
}

