#include "Pkt_Def.h"
namespace ApplicationLayerProtocol {
	//Sets all member variables of the PktDef class to zero and nullptr
	PktDef::PktDef() {
		cmdPacket.header.PktCount = cmdPacket.header.Drive = cmdPacket.header.Claw = cmdPacket.header.Arm = cmdPacket.header.Ack = cmdPacket.header.Sleep = cmdPacket.header.Status = cmdPacket.header.Padding = cmdPacket.header.length = 0;
		cmdPacket.Data = nullptr;
		cmdPacket.CRC = 0;
	}
	//Used to take in raw buffer and parse it to populate header, body, tail of packet
	PktDef::PktDef(char* buffer) {
		char* ptr = buffer;
		memcpy(&cmdPacket.header, ptr, HEADERSIZE - 1);                                      //Copies the data from the rawbuffer to populate PktCount and bitfield
		ptr += HEADERSIZE - 1;
		memcpy(&cmdPacket.header.length, ptr, sizeof(cmdPacket.header.length));				 //Copies data for the length portion of the header
		ptr += sizeof(cmdPacket.header.length);

		int size = (cmdPacket.header.length - HEADERSIZE) - sizeof(cmdPacket.CRC);			 //calculates size of the rest of packet by subtracting size of header and tail from length
		if (size > 0) {
			cmdPacket.Data = new char[size];
			memcpy(cmdPacket.Data, ptr, size);												 //Copies the data into the body of the packet based on the size of the data portion
			ptr += size;
		}
		//memcpy(&cmdPacket.CRC, ptr, sizeof(cmdPacket.CRC));									 //Copies the data for the tail or CRC portion
		CalcCRC();
	}
	//Sets the specific bit based on the cmdtype passed in
	void PktDef::SetCmd(CmdType type) {
		if (type == DRIVE) {
			cmdPacket.header.Drive = 1;													//If statements to check cmdtype and set corresponding bit to 1
		}
		else if (type == SLEEP) {
			cmdPacket.header.Sleep = 1;												//The length of data packet is 0 when receiving a sleep command
		}
		else if (type == ARM) {
			cmdPacket.header.Arm = 1;
		}
		else if (type == CLAW) {
			cmdPacket.header.Claw = 1;
		}
		else if (type == ACK) {
			cmdPacket.header.Ack = 1;
		}
	}
	//Sets the body portion of data packet based on buffer and size passed in
	void PktDef::SetBodyData(char* buffer, int size) {
		cmdPacket.Data = new char[size];
		memcpy(cmdPacket.Data, buffer, size);											//Copies the data in the body portion of packet
		cmdPacket.header.length = HEADERSIZE + size + sizeof(char);						//Calculates the length which is size of header + size of body + size of tail or CRC
	}

	//Sets the packet count to determine which packet this is
	void PktDef::SetPktCount(int size) {
		cmdPacket.header.PktCount = size;
	}

	//Used to calculate CRC based on number of bits are set to 1 in the entire data packet. 
	void PktDef::CalcCRC() {
		int counter = 0;
		char* ptr = (char*)&cmdPacket.header.PktCount;
		for (int x = 0; x < (sizeof(cmdPacket.header.PktCount) * 8); x++) {				//This for loop is used to check the number of 1s in the PktCount portion of the header
			counter += (*ptr >> x) & 1;
		}
		ptr = ptr + 4;
		for (int x = 0; x < (sizeof(char) * 8); x++) {									//Used to count number of 1s in the bit field only
			counter += (*ptr >> x) & 1;
		}
		ptr = (char*)&cmdPacket.header.length;
		for (int x = 0; x < (sizeof(cmdPacket.header.length) * 8); x++) {				//Used to count number of 1s in the length portion of the header
			counter += (*ptr >> x) & 1;
		}
		ptr = (char*)cmdPacket.Data;
		int size = (cmdPacket.header.length - HEADERSIZE) - sizeof(cmdPacket.CRC);		//Calculates size of the body based on length of packet - length of header and length of tail
		while (size > 0) {																//Will loop for each byte of the data (e.g. if 2 bytes are in the Data portion then loop 2 times)
			for (int x = 0; x < 8; x++) {												//Used to count bits sets to 1 in each byte of the data
				counter += (*ptr >> x) & 1;
			}
			size--;
			ptr++;
		}
		cmdPacket.CRC = counter;														//Will store final value in the CRC or tail
	}

	//Used to determine which command bit is set
	CmdType PktDef::GetCmd() {
		char* ptr = (char*)&cmdPacket.header.PktCount;
		ptr += sizeof(int);
		if ((*ptr & 0x01) == 0x01) {													//If statement checking each relevant bit to determine if they are set
			return DRIVE;																//and returns the type based on bit checked
		}
		else if (((*ptr >> 1) & 0x01) == 0x01) {
			return STATUS;
		}
		else if (((*ptr >> 2) & 0x01) == 0x01) {
			return SLEEP;
		}
		else if (((*ptr >> 3) & 0x01) == 0x01) {
			return ARM;
		}
		else if (((*ptr >> 4) & 0x01) == 0x01) {
			return CLAW;
		}
		else if (((*ptr >> 5) & 0x01) == 0x01) {
			return ACK;
		}
		else {
			return NONE;																//Default value in case none of the above bits are set
		}
	}
	//Used to return the value of the Ack bit whether its set or not
	bool PktDef::GetAck() {
		char* ptr = (char *)&cmdPacket;
		ptr += sizeof(int);
		//check other bits?
		return (*ptr >> 5) & 0x01;														//Shifts by 5 bits to get to the Ack bit and compares it against 1 with bitwise &
	}

	//Used to get the length of the entire data packet
	int PktDef::GetLength() {
		return (int)cmdPacket.header.length;
	}

	//Returns the data in the body and parses it to a raw char buffer
	char* PktDef::GetBodyData() {
		return (char*)cmdPacket.Data;
	}

	//Returns the pktcount in the header
	int PktDef::GetPktCount() {
		return cmdPacket.header.PktCount;
	}

	//Used to check the crc of the buffer and determine if it matches the CRC passed in as the last element of the buffer
	bool PktDef::CheckCRC(char* buf, int bytes) {
		char crc = 0;
		char * ptr = buf;
		for (int i = 0; i < bytes - 1; i++) {											//Used to loop through each byte of the buffer
			for (int n = 0; n < 8; n++)													//Used to loop through each bit of each byte
				crc += (*ptr >> n) & 0x01;												//Used to compare each bit against hex representation of 1
			ptr++;
		}


		buf += (bytes - 1);																// moves to where the crc should be in the raw data buffer
		return crc == *buf;																//compare crc to buffer crc
	}

	//Used to generate the packet and populate header,body, and tail
	char* PktDef::GenPacket() {
		RawBuffer = new char[cmdPacket.header.length];
		char* ptr = RawBuffer;

		memcpy(ptr, &cmdPacket.header, HEADERSIZE - 1);												//cpy header data including flags but not including length
		ptr += HEADERSIZE - 1;
		memcpy(ptr, &cmdPacket.header.length, sizeof(cmdPacket.header.length));						//used to copy the length data from the header
		ptr += sizeof(cmdPacket.header.length);

		int size = (cmdPacket.header.length - HEADERSIZE) - sizeof(cmdPacket.CRC);					//Calculates the size of the data by - header + tail from length
		memcpy(ptr, cmdPacket.Data, size);															//copies the data information into the RawBuffer
		ptr += size;

		memcpy(ptr, &cmdPacket.CRC, sizeof(char));													//copy crc value into the rawbuffer
		return RawBuffer;
	}
}