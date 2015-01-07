#pragma once
#include <memory>

#include "ClientSocket.h"
#include "ConnectionException.h"
#include "ServerCommand.h"
#include "SyncQueue.h"

class ClientSocket;
class NetworkServices
{
public:
	NetworkServices();
	~NetworkServices();
    
    bool ConnectToServer();
private:
    static const std::string HOST_IP;
    static const int HOST_PORT;
    static Sync_queue<ServerCommand> queue;
    
    std::unique_ptr<ClientSocket> clientSocket;
    
    void ConsumeServerCommands();
};