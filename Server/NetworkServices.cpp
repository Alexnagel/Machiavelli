#include "NetworkServices.h"

const int NetworkServices::PORT = 81;

NetworkServices::NetworkServices()
{
}

bool NetworkServices::StartServer()
{
    try {
        serverSocket = std::unique_ptr<ServerSocket>(new ServerSocket(PORT));
        return true;
    } catch (std::exception& e) {
        std::cout << e.what();
        return false;
    }
}

NetworkServices::~NetworkServices()
{
}
