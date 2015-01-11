#pragma once
#include <thread>
#include <exception>
#include <memory>
#include <iostream>
#include <vector>

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"

#include "GameManager.h"

#include "ServerSocket.h"

class NetworkServices
{
public:
	NetworkServices(std::unique_ptr<GameManager> p_gameManager);
    ~NetworkServices();
    
    bool StartServer();
    void ListenForClients();
    
    void WriteToClient(std::string command, std::shared_ptr<Socket> socket);
    void WriteToClient(std::string command, std::shared_ptr<Socket> socket, bool prompt);
    std::string PromptClient(std::shared_ptr<Socket> socket);
private:
    static const int PORT;
    std::unique_ptr<GameManager> gameManager;
    
    std::unique_ptr<ServerSocket> serverSocket;
    
    void ConsumeCommand();
    void HandleClient(Socket* socket);
};

