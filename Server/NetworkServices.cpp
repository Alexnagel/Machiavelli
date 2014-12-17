#include "NetworkServices.h"

static int NetworkServices::PORT = 81;

NetworkServices::NetworkServices()
{
}

bool NetworkServices::StartServer()
{
    try {
        serverSocket = std::unique_ptr<ServerSocket>(new ServerSocket(PORT));
    } catch (catch parameter) {
        <#statements#>
    }
}

NetworkServices::~NetworkServices()
{
}
