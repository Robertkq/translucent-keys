#pragma once

#include "common.h"
#include "kqnet.h"
#include <format>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

class Server : public kq::server_interface<messageType> {
  public:
    Server(uint16_t port, uint64_t (*scrambleFunc)(uint64_t));

    bool OnClientConnect(kq::connection<messageType>* client) override;
    void OnClientDisconnect(kq::connection<messageType>* client) override;
    void OnClientValidated(kq::connection<messageType>* client) override;
    void OnClientUnvalidated(kq::connection<messageType>* client) override;
    void OnMessage(kq::connection<messageType>* client,
                   kq::message<messageType>& msg) override;

    void StartServer();
    void StopServer();

    void sendListOfTargets();

  private:
    void LoopServer();
    std::string ipToStr(const asio::ip::tcp::endpoint& endpoint);

  private:
    std::vector<kq::connection<messageType>*> targets;
    std::vector<kq::connection<messageType>*> clients;
    std::unordered_map<uint32_t, std::string> nameMap;
};