#include "server.h"

using namespace kq;

Server::Server(uint16_t port, uint64_t (*scrambleFunc)(uint64_t))
    : server_interface<messageType>(port, scrambleFunc) {}

bool Server::OnClientConnect(connection<messageType>* client) {
    std::cout << std::format("[{}] connected to me!\n",
                             ipToStr(client->getIP()));
    return true;
}

void Server::OnClientDisconnect(connection<messageType>* client) {
    std::cout << std::format("[{}] disconnected from me!\n",
                             ipToStr(client->getIP()));
}

void Server::OnClientValidated(connection<messageType>* client) {
    std::cout << std::format("[{}] succeded connecting to me!\n",
                             ipToStr(client->getIP()));
}

void Server::OnClientUnvalidated(connection<messageType>* client) {
    std::cout << std::format("[{}] failed connecting to me!\n",
                             ipToStr(client->getIP()));
}

void Server::sendListOfTargets() {
    kq::message<messageType> msg(messageType::listOfTargets);

    for (auto& [targetID, name] : nameMap) {
        for (auto c : name) {
            msg << (char)c;
        }
        msg << (uint32_t)name.size();
        msg << (uint32_t)targetID;
    }
    msg << (uint32_t)nameMap.size();
    for (auto receiver : clients) {
        receiver->Send(msg);
    }
}

void Server::OnMessage(connection<messageType>* client,
                       message<messageType>& msg) {
    switch (msg.getID()) {
    case (messageType::targetConnected): {
        targets.push_back(client);
        std::string name;
        uint32_t size;
        msg >> size;
        for (uint32_t i = 0; i < size; ++i) {
            char c;
            msg >> c;
            name.insert(name.begin(), c);
        }
        std::cout << std::format("Registered [{}, {}, {}] as target!\n",
                                 ipToStr(client->getIP()), client->getID(),
                                 name);
        nameMap[client->getID()] = name;
        sendListOfTargets();
        break;
    }
    case (messageType::targetDisconnected): {
        std::cout << std::format("Unregistered [{}, {}] as target!\n",
                                 ipToStr(client->getIP()), client->getID());
        targets.erase(std::find(targets.begin(), targets.end(), client));
        break;
    }
    case (messageType::clientConnected): {
        std::cout << std::format("Registered [{}, {}] as client!\n",
                                 ipToStr(client->getIP()), client->getID());
        clients.push_back(client);
        sendListOfTargets();
        break;
    }
    case (messageType::clientDisconnected): {
        std::cout << std::format("Unregistered [{}, {}] as client!\n",
                                 ipToStr(client->getIP()), client->getID());
        clients.erase(std::find(clients.begin(), clients.end(), client));
        break;
    }
    case (messageType::targetTyped): {
        msg << client->getID();
        for (auto receiver : clients) {
            receiver->Send(msg);
        }
        break;
    }
    } // switch
}

void Server::StartServer() {
    std::cout << std::format("Starting server...\n");
    if (!Start()) {
        std::cout << std::format("Server failed start up!\n");
        return;
    }
    std::cout << std::format("Server started successfuly!\n");
    LoopServer();
}

void Server::StopServer() {
    std::cout << std::format("Stopping server...\n");
    Stop();
}

void Server::LoopServer() {
    while (true) {
        Update();
    }
}

std::string Server::ipToStr(const asio::ip::tcp::endpoint& endpoint) {
    std::ostringstream os;
    os << endpoint;

    return os.str();
}
