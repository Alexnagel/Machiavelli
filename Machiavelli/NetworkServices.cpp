#include "NetworkServices.h"

// Set statics
const std::string NetworkServices::HOST_IP = "127.0.0.1";
const int NetworkServices::HOST_PORT = 81;


NetworkServices::NetworkServices()
{
}

bool NetworkServices::ConnectToServer()
{
    try
    {
        clientSocket = std::unique_ptr<ClientSocket>(new ClientSocket(HOST_IP.c_str(), HOST_PORT));
    }
    catch (const ConnectionException &e)
    {
		std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

void NetworkServices::ConsumeServerCommands()
{
    while (true)
    {
        ServerCommand serverCommand;
        //queue.get(serverCommand);
        //std::shared_ptr<clientSocket>
        
    }
}

NetworkServices::~NetworkServices()
{
}
