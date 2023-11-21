#include "server.h"

using namespace kq;

Server::Server(uint16_t port, uint64_t(*scrambleFunc)(uint64_t))
	: server_interface<messageType>(port, scrambleFunc)
{}

bool Server::OnClientConnect(connection<messageType>* client) 
{
	std::cout << client->getIP() << " connected to me!\n";
	return true;
}

void Server::OnClientDisconnect(connection<messageType>* client) 
{
	std::cout << client->getIP() << " disconnected to me!\n";
}

void Server::OnClientValidated(connection<messageType>* client) 
{
	std::cout << client->getIP() << " succeded connecting to me!\n";
}

void Server::OnClientUnvalidated(connection<messageType>* client) 
{
	std::cout << client->getIP() << " failed connecting to me!\n";
}

void Server::OnMessage(connection<messageType>* client, message<messageType>& msg) 
{
	switch (msg.getID())
	{
	case(messageType::targetConnected):
	{
		targets.push_back(client);
		break;
	}
	case(messageType::targetDisconnected):
	{
		targets.erase(std::find(targets.begin(), targets.end(), client));
		break;
	}
	case(messageType::clientConnected):
	{
		clients.push_back(client);
		break;
	}
	case(messageType::clientDisconnected):
	{
		clients.erase(std::find(clients.begin(), clients.end(), client));
		break;
	}
	case(messageType::targetTyped):
	{
		for (auto client : clients)
		{
			client->Send(msg);
		}
		break;
	}
		

	}
}


