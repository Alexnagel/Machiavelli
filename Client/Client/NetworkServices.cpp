#include "NetworkServices.h"

// Set statics
const std::string NetworkServices::HOST_IP = "127.0.0.1";
//const std::string NetworkServices::HOST_IP = "188.166.3.223";
const int NetworkServices::HOST_PORT = 1080;


NetworkServices::NetworkServices()
{
}

bool NetworkServices::ConnectToServer()
{
	try
	{
		clientSocket = std::unique_ptr<ClientSocket>(new ClientSocket(HOST_IP.c_str(), HOST_PORT));

        serverHandler = std::thread{ &NetworkServices::ConsumeServerCommands, this };
		userHandler = std::thread{ &NetworkServices::ConsumeUserCommands, this };
	}
	catch (const ConnectionException &e)
	{
		std::cout << e.what() << std::endl;
		isConnected = false;
		return false;
	}
    catch(...)
    {
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

void NetworkServices::WaitForThreads()
{
    serverHandler.join();
    userHandler.join();
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
            if (cmd == "<emptymessage>")
            {
                cmd = "";
                WriteCommand("<stoplistening>\n");
                continue;
            }
            if (cmd == "<line>\n")
            {
                cmd = "";
                for (int i = 0; i < 80; i++)
                {
                    cmd.append("-");
                }
            }
            if (cmd == "<connectionclosed>")
                break;

			std::cerr << cmd << newlineString;
		}
		catch (std::exception &e)
		{
			std::cerr << e.what();
            break;
		}
        catch(...)
        {
            break;
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
