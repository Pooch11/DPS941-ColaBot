#include <iostream>

namespace ApplicationLayerProtocol {
	enum CmdType { DRIVE, STATUS, SLEEP, ARM, CLAW, ACK, NONE };	//Defines the cmdTypes available for the robot to receive

	const int FORWARD = 1;									//Values that will be called later in the code
	const int BACKWARD = 2;
	const int RIGHT = 3;
	const int LEFT = 4;
	const int UP = 5;
	const int DOWN = 6;
	const int OPEN = 7;
	const int CLOSE = 8;
	const int HEADERSIZE = 6;

	struct MotorBody {										//Defines structure of the body portion of the data packet
		unsigned char Direction;
		unsigned char Duration;
	};

	struct Header {											//Defines structure for the header portion
		int PktCount;
		unsigned Drive : 1;
		unsigned Status : 1;
		unsigned Sleep : 1;
		unsigned Arm : 1;
		unsigned Claw : 1;
		unsigned Ack : 1;
		unsigned Padding : 2;
		unsigned char length;
	};

	class PktDef {
	private:
		struct CmdPacket {									//Represents the packet structure with a header, body, and tail or CRC.
			Header header;
			char* Data;
			char CRC;
		} cmdPacket;
		char* RawBuffer;
	public:
		PktDef();
		PktDef(char*);
		void SetCmd(CmdType);
		void SetBodyData(char*, int);
		void SetPktCount(int);
		CmdType GetCmd();
		bool GetAck();
		int GetLength();
		char* GetBodyData();
		int GetPktCount();
		bool CheckCRC(char*, int);
		void CalcCRC();
		char* GenPacket();
	};
}