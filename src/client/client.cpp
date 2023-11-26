#include "client.h"

Client::Client(uint64_t(*scrambleFunc)(uint64_t))
    : kq::client_interface<messageType>(scrambleFunc),
	logger("client_output.txt", "./"),
	networkingThread(&Client::networkInitAndLoop, this), networkLoop(true)
{

}

Client::~Client()
{
	logger.out(KQINFO, { "Disconnecting from server...\n" });
	networkLoop = false;
	Disconnect();
}


void Client::networkInitAndLoop()
{
	logger.out(KQINFO, { "Connecting to server...\n" });
	if (Connect("192.168.0.105", 60000))
	{
		logger.out(KQINFO, { "Failed connecting to server!\n" });
		return;
	}
	logger.out(KQINFO, { "Successfuly connected to server!\n" });
	while (networkLoop)
	{
		
	}
}