#pragma once
#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <sys/socket.h>			/* Include Winsock libraries */
#include <sys/types.h>
#include <iostream>	

static bool ExeComplete = false;

enum SocketType { CLIENT, SERVER };
enum ConnectionType { TCP, UDP };
const int DEFAULT_SIZE = 100;

class MySocket {
	char *Buffer;
	SOCK_STREAM WelcomeSocket;
	SOCK_STREAM ConnectionSocket;
	struct sockaddr_in SvrAddr;
	SocketType mySocket;
	std::string IPAddr;
	int port;
	ConnectionType connectionType;
	bool bTCPConnect;
	int MaxSize;

	bool connectSocket(SOCK_STREAM&, int, int);

public:
	MySocket(SocketType, std::string, unsigned int, ConnectionType, unsigned int size = DEFAULT_SIZE);
	~MySocket();
	void SendData(const char*, int);
	int GetData(char*);
	std::string GetIPAddr();
	void SetIPAddr(std::string);
	void setPort(unsigned int);
	int getPort();
	SocketType GetType();
	void SetType(SocketType);
	void ConnectTCP();
	void DisconnectTCP();
};

#endif