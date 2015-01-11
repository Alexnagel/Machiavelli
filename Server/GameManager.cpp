#include "GameManager.h"
#include "NetworkServices.h"

GameManager::GameManager()
{
    networkServices = std::unique_ptr<NetworkServices>(new NetworkServices(
                                                                           std::unique_ptr<GameManager>(this)));
    if (networkServices->StartServer())
    {
        // Starting server was success, now listen for clients
        networkServices->ListenForClients();
    }
    else
    {
        std::cerr << "Error starting the Machiavelli server";
    }
    
}

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
		
		// Let the player choose a card
		GetPlayerCard(first_player);

		socket->write("You can choose a card");
	}
}

void GameManager::GetPlayerCard(std::shared_ptr<Player> player)
{
	int counter = 0;
	for (int i = 0; i < players.size(); i++)
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
			first_player->GetSocket()->write("Available cards:\n");
			for (int i = 0; i < player_card_deck.Size(); i++)
			{
				first_player->GetSocket()->write(player_card_deck.Get(i)->GetName() + "\n");
			}

			// Let the user pick a card...
			first_player->GetSocket()->write("Choose your card:\n");
			std::string card_name = socket->readline();

			// Check if this card exists
			if (card_name == "builder") {
				card_not_set = false;
				for (int i = 0; i < player_card_deck.Size(); i++)
				{
					if (player_card_deck.Get(i)->GetName() == "builder")
					{
						first_player->AddPlayerCard(player_card_deck.Get(i));
						player_card_deck.Remove(i);
						break;
					}
				}
			} else if (card_name == "builder") {
				card_not_set = false;
			} else if (card_name == "builder") {
				card_not_set = false;
			} else if (card_name == "builder") {
				card_not_set = false;
			}
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

int GameManager::GetPlayerAmount() const
{
    return (int)players.size();
}

std::shared_ptr<Player> GameManager::AddPlayer(std::string name, std::shared_ptr<Socket> socket)
{
	if (name.empty())
		name = &"Player" [ players.size()];

	// Add the player
    std::shared_ptr<Player> player = std::make_shared<Player>(name);
    player->SetSocket(socket);
	players.push_back(player);
    
    return player;
}

GameManager::~GameManager()
{
}