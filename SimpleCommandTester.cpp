#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>

//BB-UART Serial Information
#define PORT "/dev/ttyO4"
#define BAUDRATE B115200

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
char read_buffer[2];
char write_buffer[1];
PktDef ThePacket[1];
PktDef& packPacket(char Direction, char Action) 
{
	
}
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
	options.c_cc[VMIN] = 2; //size of packet
	options.c_cc[VTIME] = 0;
	tcflush(uart_stream, TCIFLUSH);
	tcsetattr(uart_stream, TCSANOW, &options);

	std::cout << sizeof(PktDef) << std::endl;
	//if client is connected
	while (uart_stream != -1)
	{
		RxBytes(uart_stream, read_buffer, sizeof(read_buffer));
		std::cout << read_buffer << std::endl;

		std::cin >> write_buffer;
		TxBytes(uart_stream, write_buffer, sizeof(write_buffer));
	}

	getchar();
	getchar();

}
