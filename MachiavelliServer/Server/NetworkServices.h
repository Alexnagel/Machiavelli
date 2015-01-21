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

enum KeywordReturn {
    QUIT,
    STARTGAME,
    INFO,
    NONE
};


class NetworkServices
{
public:
	NetworkServices(std::unique_ptr<GameManager> p_gameManager);
    ~NetworkServices();
    
    bool StartServer();
    void ListenForClients();
    
    void WriteToClient(std::string command, std::shared_ptr<Socket> socket);
    void WriteToClient(std::string command, std::shared_ptr<Socket> socket, bool prompt);
    void WriteToAllClients(std::string command);
    void WriteToAllExceptCurrent(std::string command, std::shared_ptr<Player> player);
    
    std::string PromptClient(std::shared_ptr<Player> player);
private:
    static const int PORT;
    std::unique_ptr<GameManager> gameManager;
    
    std::unique_ptr<ServerSocket> serverSocket;
    
    void ConsumeCommand();
    void HandleClient(Socket* socket);
    KeywordReturn CheckForKeywords(std::string cmd, std::shared_ptr<Player> player);
};


