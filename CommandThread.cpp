#include "MySocket.h"
#include "Pkt_Def.h"
#include <thread>
#include <string>
#include <iostream>
#include  <iomanip>
using namespace ApplicationLayerProtocol;

void CommandThread(std::string ip, unsigned int port) {
	MySocket sock(CLIENT, ip, port, TCP, DEFAULT_SIZE);
	sock.ConnectTCP();

	int count = 0;
	while (!ExeComplete) {

		PktDef packet;
		MotorBody data;
		int choice = 0, direction = 0, time = 0;

		std::cout << "Enter 1 to drive the robot\nEnter 2 to put the robot to sleep\nEnter 3 to move the arm\nEnter 4 to either open or close the claw\n";
		std::cin >> choice;
		if (choice == 1) {
			packet.SetCmd(DRIVE);
			std::cout << "Enter 1 to move forward\nEnter 2 to move backward\nEnter 3 to move right\nEnter 4 to move left\n";
			std::cin >> direction;
			if (direction > 0 && direction < 5) {
				data.Direction = direction;
				std::cout << "How long will you like to perform this function on the robot?\n";
				std::cin >> time;
			}
			else {
				std::cout << "Invalid number entered!" << std::endl;
			}

		}
		else if (choice == 2) {
			packet.SetCmd(SLEEP);
			data.Direction = 0;
			data.Duration = 0;

		}
		else if (choice == 3) {
			packet.SetCmd(ARM);
			std::cout << "Enter 1 to lift the claw up\nEnter 2 to lower the arm down\n";
			std::cin >> direction;
			if (direction == 1) {
				data.Direction = UP;
			}
			else if (direction == 2) {
				data.Direction = DOWN;
			}
			else {
				std::cout << "Invalid number entered!" << std::endl;
			}
		}
		else if (choice == 4) {
			packet.SetCmd(CLAW);
			std::cout << "Enter 1 to open the claw\nEnter 2 to close the claw\n";
			std::cin >> direction;
			if (direction == 1) {
				data.Direction = OPEN;
			}
			else if (direction == 2) {
				data.Direction = CLOSE;
			}
			else {
				std::cout << "Invalid number entered!" << std::endl;
			}
		}
		else {
			std::cout << "Invalid number entered!" << std::endl;
		}


		if (packet.GetCmd() != NONE) {
			count++;

			if (time > 0 && packet.GetCmd() == DRIVE) {
				data.Duration = time;
			}
			else {
				data.Duration = 0;
			}

			packet.SetPktCount(count);

			packet.SetBodyData((char*)&data, 2);

			packet.CalcCRC();

			char* buffer = packet.GenPacket();
			sock.SendData(buffer, packet.GetLength());

			//recvs ack pkt
			char* rcvbuffer = new char[9];
			sock.GetData(rcvbuffer);
			PktDef packet2(rcvbuffer);
			if (!packet2.GetAck()) {
				std::cout << "Packet not acknowledged!" << std::endl;
			}
			else {
				if (packet.GetCmd() == SLEEP) {
					sock.DisconnectTCP();
					ExeComplete = true;
					std::cout << "Goodbye!" << std::endl;
				}
			}
		}
	}
}

void TelemetryThread(std::string ip, unsigned int port) {

	MySocket teleSocket(CLIENT, ip, port, TCP, DEFAULT_SIZE);

	teleSocket.ConnectTCP();

	std::cout << "Getting telemetry: " << std::endl;
	while (true) {
		char * recvBuffer = new char[DEFAULT_SIZE];
		memset(recvBuffer, '\0', DEFAULT_SIZE);

		//receive telemetry packets
		teleSocket.GetData(recvBuffer);
		PktDef statusPkt(recvBuffer);

		//verify crc & status
		if (statusPkt.CheckCRC(recvBuffer, statusPkt.GetLength()))
		{
			// display info
			if (statusPkt.GetCmd() == STATUS) // status flag == 1
			{
				//display raw data
				char * body = new char[statusPkt.GetLength()];
				memcpy(body, statusPkt.GetBodyData(), statusPkt.GetLength());

				for (int i = 0; i < statusPkt.GetLength(); i++) {
					std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)*recvBuffer << " ";
					recvBuffer++;
				}
				std::cout << std::dec << std::endl;

				//extract decimal info
				short sonar, armPos;
				memcpy(&sonar, body, sizeof(short));
				body += sizeof(short);
				memcpy(&armPos, body, sizeof(short));
				body += sizeof(short);

				bool drive;
				std::string arm, claw;
				drive = *body & 0x01;
				if ((*body >> 1) & 0x01)
					arm = "Arm is Up";
				else
					arm = "Arm is Down";
				if ((*body >> 3) & 0x01)
					claw = "Claw is Open";
				else
					claw = "Claw is Closed";

				std::cout << "Sonar: " << sonar << std::endl << "Arm Position: " << armPos << std::endl;
				std::cout << "Drive Flag: " << drive << std::endl;
				std::cout << "Arm flag: " << arm << std::endl << "Claw flag: " << claw << std::endl;

			}
		}

	}
}

