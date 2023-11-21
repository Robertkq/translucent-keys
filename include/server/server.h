#pragma once

#include <iostream>
#include "kqnet.h"
#include "common.h"

class Server : public kq::server_interface<messageType>
{
public:
	Server(uint16_t port, uint64_t(*scrambleFunc)(uint64_t));

	bool OnClientConnect(kq::connection<messageType>* client) override;
	void OnClientDisconnect(kq::connection<messageType>* client) override;
	void OnClientValidated(kq::connection<messageType>* client) override;
	void OnClientUnvalidated(kq::connection<messageType>* client) override;
	void OnMessage(kq::connection<messageType>* client, kq::message<messageType>& msg) override;
private:

};