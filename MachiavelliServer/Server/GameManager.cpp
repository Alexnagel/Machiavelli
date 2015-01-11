#include "GameManager.h"
#include "NetworkServices.h"

GameManager::GameManager()
{
    networkServices = std::unique_ptr<NetworkServices>(new NetworkServices(std::unique_ptr<GameManager>(this)));
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
		// Pop the first character card of the deck
		player_card_deck.RemoveLast();
		
		// Let the player choose a card
		GetPlayerCard();

		// Start the game rounds
		StartRound();
	}
}

void GameManager::GetPlayerCard()
{
	int counter = 0;
	for (int i = 0; i < players.size(); i++)
	{
		std::shared_ptr<Player> player;
		std::shared_ptr<PlayerCard> card;

		// Set Player
		if (counter - i <= 0)
			player = players.at(i);
		else
			player = players.at(counter - i);

		// Get the socket
		std::shared_ptr<Socket> socket = player->GetSocket();

		// Remove the first character card of the deck
		player_card_deck.RemoveLast();

		// Let the player choose a card
		bool card_not_set = true;
		while (card_not_set)
		{
			// print cards
            std::string availableCards = "Available cards:\n\n";
			for (int i = 0; i < player_card_deck.Size(); i++)
			{
				availableCards.append(player_card_deck.Get(i)->GetName() + "\n");
			}
			availableCards.append("\n");
            networkServices->WriteToClient(availableCards, socket, false);

			// Let the user pick a card...
			networkServices->WriteToClient("Choose your card\n", socket);
            std::string card_name = Utils::ToLowerCase(networkServices->PromptClient(socket));

			// Check if this card exists
			card_not_set = CheckCard(card_name, player);
			if (card_not_set)
				networkServices->WriteToClient("This is not a valid card", socket);
		}

		// Add the card to the player
		player->AddPlayerCard(card);

		// Shuffle the deck
		player_card_deck.Shuffle();
	}
}

void GameManager::StartRound()
{

}

void GameManager::EndGame()
{

}

bool GameManager::CheckCard(std::string card_name, std::shared_ptr<Player> player)
{
	if (card_name == "builder") {
		AddCard(PlayerCardType::BUILDER, player);
		return false;
	} else if (card_name == "condottiere") {
		AddCard(PlayerCardType::CONDOTTIERE, player);
		return false;
	} else if (card_name == "king") {
		AddCard(PlayerCardType::KING, player);
		return false;
	} else if (card_name == "magician") {
		AddCard(PlayerCardType::MAGICIAN, player);
		return false;
	} else if (card_name == "merchant") {
		AddCard(PlayerCardType::MERCHANT, player);
		return false;
	} else if (card_name == "murderer") {
		AddCard(PlayerCardType::MURDERER, player);
		return false;
	} else if (card_name == "preacher") {
		AddCard(PlayerCardType::PREACHER, player);
		return false;
	} else if (card_name == "thief") {
		AddCard(PlayerCardType::THIEF, player);
		return false;
	} else {
		return true;
	}
}

void GameManager::AddCard(PlayerCardType type, std::shared_ptr<Player> player)
{
	for (int i = 0; i < player_card_deck.Size(); i++)
	{
		if (player_card_deck.Get(i)->GetType() == type)
		{
			player->AddPlayerCard(player_card_deck.Get(i));
			player_card_deck.Remove(i);
			break;
		}
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