#pragma once

#include <iostream>
#include <sstream>
#include "kqnet.h"
#include <kqlog.h>
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

	void StartServer();
	void StopServer();

private:
	void LoopServer();
	std::string ipToStr(const asio::ip::tcp::endpoint& endpoint);

private:
	std::vector<kq::connection<messageType>*> targets;
	std::vector<kq::connection<messageType>*> clients;

	kq::logger<kq::default_symbols> logger;
};