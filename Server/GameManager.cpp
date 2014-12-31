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
	socket->write("Welcome to the Machiavelli Server!\n");
	socket->write("What is your name?\n");
	socket->write(socketexample::prompt);

	// Add the player
	std::string username = socket->readline();
	
	std::shared_ptr<Player> player;
	if (username.empty())
		player = std::make_shared<Player>("Player" + std::to_string(players.size()));
	else
		player = std::make_shared<Player>(username);

	// Add the player
	players.push_back(player);

	// Create a welcome message
	player->GetSocket()->write("Welcome " + player->GetName() + "!\n\n");

	// Show the user how to quit
	player->GetSocket()->write("To exit this Machiavelli server enter 'quit'.\n");

	while (true) { // game loop
		try {
			// read first line of request
			std::string cmd = player->GetSocket()->readline();
			std::cerr << "client (" << player->GetSocket()->get() << ") said: " << cmd << '\n';

			ClientCommand command{ cmd, player->GetSocket() };

			if (cmd == "quit") 
			{
				player->GetSocket()->write("Bye!\n");
				break; // out of game loop, will end this thread and close connection
			}
			else if (cmd == "start")
			{
				if (players.size() > 1)
				{
					Start();

					// Show that the game has started
					command = ClientCommand{ "The game has started!", player->GetSocket() };
					queue.put(command);
				}
				else
				{
					std::string output = "There need to be atleast 2 players to start the game.\n";
					output.append("Players in lobby: ");
					output.append(std::to_string(players.size()));

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

#pragma endregion

void GameManager::Start()
{
	// Init decks
	building_card_deck = Parser::LoadBuildingFile();
	player_card_deck = Parser::LoadCharacterFile();

	// Shuffle the decks
	player_card_deck.Shuffle();
	building_card_deck.Shuffle();

	// The first player may choose his cards
	if (players.size() > 1)
	{
		std::shared_ptr<Player> first_player = players.at(0);
		std::shared_ptr<Socket> socket = first_player->GetSocket();

		// Pop the first character card of the deck
		player_card_deck.RemoveLast();
		

		socket->write("You can choose a card");
	}
}

void GameManager::GetPlayerCard(std::shared_ptr<Player> player)
{
	int counter = 0;
	for (int i = 0; i < player_card_deck.Size(); i++)
	{
		std::shared_ptr<Player> first_player;
		std::shared_ptr<PlayerCard> card;

		// Set Player
		if (counter - i <= 0)
			first_player = players.at(i);
		else
			first_player = players.at(counter - i);

		// Get the socket
		std::shared_ptr<Socket> socket = first_player->GetSocket();

		// Remove the first character card of the deck
		player_card_deck.RemoveLast();

		// Let the player choose a card
		bool card_not_set = true;
		while (card_not_set)
		{
			// print cards
			// Let the user pick a card...
			// Check if this card exists
		}

		// Add the card to the player
		player->AddPlayerCard(card);

		// Shuffle the deck
		player_card_deck.Shuffle();
	}
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