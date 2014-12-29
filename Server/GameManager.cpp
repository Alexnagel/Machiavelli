#include "GameManager.h"

namespace socketexample {
	const int tcp_port{ 1080 };
	const std::string prompt{ "> " };
}

static Sync_queue<ClientCommand> queue;

GameManager::GameManager()
{
	// start command consumer thread
	std::thread consumer{ &GameManager::ConsumeCommand, this };
	consumer.detach(); // detaching is usually ugly, but in this case the right thing to do

	// create a server socket
	ServerSocket server(socketexample::tcp_port);

	while (true) {
		try {
			// wait for connection from client; will create new socket
			std::cerr << "server listening" << '\n';
			Socket* client = nullptr;

			while ((client = server.accept()) != nullptr) {
				// communicate with client over new socket in separate thread
				std::thread handler{ &GameManager::HandleClient, this , client };
				handler.detach(); // detaching is usually ugly, but in this case the right thing to do
				std::cerr << "server listening again" << '\n';
			}
		}
		catch (const std::exception& ex) {
			std::cerr << ex.what() << ", resuming..." << '\n';
		}
	}
}

#pragma region Server

void GameManager::ConsumeCommand() // runs in its own thread
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
			client->write(socketexample::prompt);
		}
		else {
			std::cerr << "trying to handle command for client who has disappeared...\n";
		}
	}
}

void GameManager::HandleClient(Socket* socket) // this function runs in a separate thread
{
	std::shared_ptr<Socket> client{ socket };
	client->write("Welcome to the Machiavelli Server!\n");
	client->write("What is your name?\n");
	client->write(socketexample::prompt);

	// Add the player
	std::string username = client->readline();
	AddPlayer(username);

	// Create a welcome message
	client->write("Welcome " + username + "!\n\n");

	// Show the user how to quit
	client->write("To exit this Machiavelli server enter 'quit'.\n");

	while (true) { // game loop
		try {
			// read first line of request
			std::string cmd = client->readline();
			std::cerr << "client (" << client->get() << ") said: " << cmd << '\n';

			ClientCommand command{ cmd, client };

			if (cmd == "quit") 
			{
				client->write("Bye!\n");
				break; // out of game loop, will end this thread and close connection
			}
			else if (cmd == "start")
			{
				if (players.size() > 1)
				{
					Start();

					// Show that the game has started
					command = ClientCommand{ "The game has started!", client };
					queue.put(command);
				}
				else
				{
					std::string output = "There need to be atleast 2 players to start the game.\n";
					output.append("Players in lobby: ");
					output.append(std::to_string(players.size()));

					// Show the error message
					command = ClientCommand{ output, client };
					queue.put(command);
				}
			}
		}
		catch (const std::exception& ex) {
			client->write("ERROR: ");
			client->write(ex.what());
			client->write("\n");
		}
		catch (...) {
			client->write("ERROR: something went wrong during handling of your request. Sorry!\n");
		}
	}
}

#pragma endregion

void GameManager::Start()
{
	// Init decks
	building_card_deck = Parser::LoadBuildingFile();
	player_card_deck = Parser::LoadCharacterFile();

	// Shuffle the decks
	player_card_deck.Shuffle();
	building_card_deck.Shuffle();
}

std::shared_ptr<Player> GameManager::GetPlayer(int i) const
{
	if (players.size() > i)
		return players.at(i);
	else
		return nullptr;
}

void GameManager::AddPlayer(std::string name)
{
	if (name.empty())
		name = "Player" + players.size();

	// Add the player
	players.push_back(std::make_shared<Player>(name));
}

GameManager::~GameManager()
{
}