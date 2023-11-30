#include "server.h"

using namespace kq;

Server::Server(uint16_t port, uint64_t(*scrambleFunc)(uint64_t))
	: server_interface<messageType>(port, scrambleFunc),
	logger("server_output.txt", "./")
{}

bool Server::OnClientConnect(connection<messageType>* client) 
{
	logger.out(KQINFO, { "[{}] connected to me!\n", ipToStr(client->getIP()) });
	return true;
}

void Server::OnClientDisconnect(connection<messageType>* client) 
{
	logger.out(KQINFO, { "[{}] disconnected from me!\n", ipToStr(client->getIP()) });
}

void Server::OnClientValidated(connection<messageType>* client) 
{
	logger.out(KQINFO, { "[{}] succeded connecting to me!\n", ipToStr(client->getIP()) });
}

void Server::OnClientUnvalidated(connection<messageType>* client) 
{
	logger.out(KQINFO, { "[{}] failed connecting to me!\n", ipToStr(client->getIP()) });
}

void Server::OnMessage(connection<messageType>* client, message<messageType>& msg) 
{
	switch (msg.getID())
	{
	case(messageType::targetConnected):
	{
		logger.out(KQINFO, { "Registered [{}, {}] as target!\n", ipToStr(client->getIP()), client->getID() });
		targets.push_back(client);
		break;
	}
	case(messageType::targetDisconnected):
	{
		logger.out(KQINFO, { "Unregistered [{}, {}] as target!\n", ipToStr(client->getIP()), client->getID() });
		targets.erase(std::find(targets.begin(), targets.end(), client));
		break;
	}
	case(messageType::clientConnected):
	{
		logger.out(KQINFO, { "Registered [{}, {}] as client!\n", ipToStr(client->getIP()), client->getID() });
		clients.push_back(client);
		break;
	}
	case(messageType::clientDisconnected):
	{
		logger.out(KQINFO, { "Unregistered [{}, {}] as client!\n", ipToStr(client->getIP()), client->getID() });
		clients.erase(std::find(clients.begin(), clients.end(), client));
		break;
	}
	case(messageType::targetTyped):
	{
		msg << client->getID();
		for (auto client : clients)
		{
			client->Send(msg);
		}
		break;
	}
	} // switch
}

void Server::StartServer()
{
	logger.out(KQINFO, { "Starting server...\n" });
	if (!Start())
	{
		logger.out(KQERROR, { "Server failed start up!\n" });
		return;
	}
	logger.out(KQINFO, { "Server started successfuly!\n" });
	LoopServer();
}

void Server::StopServer()
{
	logger.out(KQINFO, { "Stopping server...\n" });
	Stop();
}

void Server::LoopServer()
{
	while (true)
	{
		Update();
	}
}

std::string Server::ipToStr(const asio::ip::tcp::endpoint& endpoint)
{
	std::ostringstream os;
	os << endpoint;

	return os.str();
}


