#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>

//BB-UART Serial Information
#define PORT "/dev/ttyO4"
#define BAUDRATE B115200

int main(void) {
	int uart_stream = -1;
	uart_stream = open(PORT, O_RDWR);
	if (uart_stream == -1)
	{
		std::cout << "Failed to open BB-UART" << std::endl;
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
	tcflush(uart_stream, TCIFLUSH);
	tcsetattr(uart_stream, TCSANOW, &options);
}