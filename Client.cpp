#include "MySocket.h"
#include "Pkt_Def.h"
#include <thread>


using namespace ApplicationLayerProtocol;

void CommandThread(std::string ip, unsigned int port);
void TelemetryThread(std::string ip, unsigned int port);

int main(int argc, char* argv[]) {
	std::string ip = argv[1];
	unsigned int Cmdport = std::atoi(argv[2]);

	std::thread(CommandThread, ip, Cmdport).detach();

	while (!ExeComplete) {
	};
}