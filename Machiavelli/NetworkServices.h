#pragma once
#include "ClientSocket.h"

#include "ConnectionException.h"

class NetworkServices
{
public:
	NetworkServices();
	~NetworkServices();
    
    bool ConnectToServer();
private:
    static const std::string HOST_IP;
    static const int HOST_PORT;
    
    std::unique_ptr<ClientSocket> clientSocket;
};