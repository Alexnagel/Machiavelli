#include "NetworkServices.h"

// Set statics
const std::string NetworkServices::HOST_IP = "127.0.0.1";
const int NetworkServices::HOST_PORT = 1080;


NetworkServices::NetworkServices()
{
}

bool NetworkServices::ConnectToServer()
{
    try
    {
        clientSocket = std::unique_ptr<ClientSocket>(new ClientSocket(HOST_IP.c_str(), HOST_PORT));
        
        std::thread serverHandler{ &NetworkServices::ConsumeServerCommands, this};
        serverHandler.detach(); // detaching is usually ugly, but in this case the right thing to do
        
        std::thread userHandler { &NetworkServices::ConsumeUserCommands, this };
        userHandler.detach();
    }
    catch (const ConnectionException &e)
    {
		std::cout << e.what() << std::endl;
        isConnected = false;
        return false;
    }
    
    isConnected = true;
    return true;
}

bool NetworkServices::IsConnected()
{
    return isConnected;
}

void NetworkServices::ConsumeServerCommands()
{
    while (true)
    {
        try
        {
            // read line of request
            std::string cmd = clientSocket->readline();
            
            std::string newlineString = "\n";
            if (cmd == "> ")
                newlineString = "";
            
            std::cerr << cmd << newlineString;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what();
        }
    }
}

void NetworkServices::ConsumeUserCommands()
{
    std::string s;
    
    // Get the user input line
    while (getline(std::cin, s))
    {
        // Write the command to the server
        WriteCommand(s);
    }
}

void NetworkServices::WriteCommand(std::string command)
{
    clientSocket->write(command + "\n");
}

NetworkServices::~NetworkServices()
{
}
