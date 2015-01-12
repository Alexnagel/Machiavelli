#pragma once
#include <memory>
#include <vector>

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
    bool IsConnected();
    void WaitForThreads();
    
	void WriteCommand(std::string command);
private:
	static const std::string HOST_IP;
	static const int HOST_PORT;
    
    std::thread serverHandler;
    std::thread userHandler;
	static Sync_queue<ServerCommand> queue;
    
	std::unique_ptr<ClientSocket> clientSocket;

	void ConsumeServerCommands();
	void ConsumeUserCommands();
	bool isConnected;
};