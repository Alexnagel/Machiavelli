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
private:
    static const int PORT;
    std::unique_ptr<GameManager> gameManager;
    
    std::unique_ptr<ServerSocket> serverSocket;
    
    void ConsumeCommand();
    void HandleClient(Socket* socket);
};

