#include "NetworkServices.h"

const int NetworkServices::PORT = 1080;
static Sync_queue<ClientCommand> queue;

NetworkServices::NetworkServices(std::unique_ptr<GameManager> p_gameManager):
    gameManager(std::move(p_gameManager))
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

void NetworkServices::ListenForClients()
{
    // start command consumer thread
    std::thread consumer{ &NetworkServices::ConsumeCommand, this };
    consumer.detach(); // detaching is usually ugly, but in this case the right thing to do
    
    while (true) {
        try {
            // wait for connection from client; will create new socket
            std::cerr << "Server listening" << '\n';
            Socket* client = nullptr;
            
            while ((client = serverSocket->accept()) != nullptr)
            {
                // communicate with client over new socket in separate thread
                std::thread handler{ &NetworkServices::HandleClient, this , client };
                handler.detach(); // detaching is usually ugly, but in this case the right thing to do
                
                std::cerr << "Server listening again" << '\n';
            }
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what() << ", resuming..." << '\n';
        }
    }
}

void NetworkServices::ConsumeCommand()
{
    while (true) {
        ClientCommand command;
        queue.get(command); // will block here unless there still are command objects in the queue
        std::shared_ptr<Socket> client{ command.get_client() };
        if (client) {
            try {
                client->write(command.get_cmd());
            }
            catch (const std::exception& ex) {
                client->write("Sorry, ");
                client->write(ex.what());
                client->write("\n");
            }
            catch (...) {
                client->write("Sorry, something went wrong during handling of your request.\n");
            }
        }
        else {
            std::cerr << "trying to handle command for client who has disappeared...\n";
        }
    }
}

void NetworkServices::HandleClient(Socket *socket)
{
    socket->write("Welcome to the Machiavelli Server!\n");
    socket->write("What is your name?\n");
    socket->write("> \n");
    
    // Add the player
    std::string username;
    
    while (username.empty())
    {
        try {
            username = socket->readline();
        }
        catch (...)
        {
            std::cerr << "hmm";
        }
    }
    
    std::shared_ptr<Player> player = gameManager->AddPlayer(username, std::make_shared<Socket>(*socket));
    
    // Create a welcome message
    player->GetSocket()->write("Welcome " + player->GetName() + "!\n\n");
    
    // Show the user how to quit
    player->GetSocket()->write("To exit this Machiavelli server enter 'quit'.\n");
    player->GetSocket()->write("To start the game enter 'start'.\n");
    player->GetSocket()->write("> \n");
    
    while (true) { // game loop
        try {
            // read first line of request
            std::string cmd;
            // Read line if the client isn't being prompted
            if (!player->GetSocket()->IsClientPrompted())
            {
                cmd = Utils::ToLowerCase(player->GetSocket()->readline());
                std::cerr << "client (" << player->GetSocket()->get() << ") said: " << cmd << '\n';
            }
            
            ClientCommand command{ cmd, player->GetSocket() };
            
            if (cmd == "quit")
            {
                player->GetSocket()->write("Bye!\n");
                player->GetSocket()->close();
                break; // out of connection loop, will end this thread and close connection
            }
            else if (cmd == "start")
            {
                if (gameManager->GetPlayerAmount() > 1)
                {
					gameManager->Start(player);
                }
                else
                {
                    std::string output = "There need to be atleast 2 players to start the game.\n";
                    output.append("Players in lobby: ");
                    output.append(std::to_string(gameManager->GetPlayerAmount()));
					output.append("\n");
                    
                    // Show the error message
                    command = ClientCommand{ output, player->GetSocket() };
                    queue.put(command);
                }
            }
        }
        catch (const std::exception& ex) {
            player->GetSocket()->write("ERROR: ");
            player->GetSocket()->write(ex.what());
            player->GetSocket()->write("\n");
        }
        catch (...) {
            player->GetSocket()->write("ERROR: something went wrong during handling of your request. Sorry!\n");
        }
    }
}

void NetworkServices::WriteToClient(std::string command, std::shared_ptr<Socket> socket, bool prompt)
{
    ClientCommand clientCommand = ClientCommand { command, socket, prompt };
    queue.put(clientCommand);
}

void NetworkServices::WriteToClient(std::string command, std::shared_ptr<Socket> socket)
{
    ClientCommand clientCommand = ClientCommand { command, socket };
    queue.put(clientCommand);
}

void NetworkServices::WriteToAllClients(std::string command)
{
    for (int i = 0; i < gameManager->GetPlayerAmount(); i++)
    {
        ClientCommand clientCommand = ClientCommand { command, gameManager->GetPlayer(i)->GetSocket() };
        queue.put(clientCommand);
    }
}

std::string NetworkServices::PromptClient(std::shared_ptr<Socket> socket)
{
    // Set to true so the readline of handleclient doesn't interfere
    socket->SetClientPrompted(true);
    
    std::string answer;
    
    while (answer.empty())
    {
        try
        {
            answer = socket->readline();
        }
        catch (...)
        {
            std::cerr << "Something went wrong reading the client response" << '\n';
        }
    }
    
    socket->SetClientPrompted(false);
    return answer;
}

NetworkServices::~NetworkServices()
{
}
