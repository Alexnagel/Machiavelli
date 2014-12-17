#pragma once
#include <string>

#include "ServerSocket.h"

class NetworkServices
{
public:
	NetworkServices();
    ~NetworkServices();
    
    bool StartServer();
private:
    static const int PORT;
    
    std::unique_ptr<ServerSocket> serverSocket;
};

