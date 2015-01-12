#include "GameManager.h"
#include "NetworkServices.h"

GameManager::GameManager() : index_king(0)
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

	// Set the number of player cards
	number_of_player_cards = player_card_deck.Size();

	// Shuffle the decks
	player_card_deck.Shuffle();
	building_card_deck.Shuffle();

	// Pop the first character card of the deck
	player_card_deck.RemoveLast();
		
	// Let the player choose a card
	GetPlayerCard();

	// Start the game rounds
	StartRound();
}

void GameManager::GetPlayerCard()
{
	// Remove the first character card of the deck
	player_card_deck.RemoveLast();

    for (int t = 0; t < 2; t++)
    {
        int counter = index_king;
        for (int i = 0; i < players.size(); i++)
        {
            std::shared_ptr<Player> player;
            
            // Set Player
            if (counter - i <= 0)
                player = players.at(i);
            else
                player = players.at(counter - i);
            
            // Get the socket
            std::shared_ptr<Socket> socket = player->GetSocket();
            
            // Let the player choose a card
            bool card_set = false;
            while (!card_set)
            {
                // print cards
                PrintPlayerCardDeck(socket);
                
                // Let the user pick a card
                networkServices->WriteToClient("Choose your card\n", socket, true);
                std::string card_name = Utils::ToLowerCase(networkServices->PromptClient(socket));
                
                // Check if this card exists
                card_set = CheckCard(card_name, player);
                if (!card_set)
                    networkServices->WriteToClient("This is not a valid card", socket);
            }
            
            // Let the player remove a card from the deck
            if (i != index_king || (i == index_king && t != 0))
            {
                bool card_removed = false;
                while (!card_removed)
                {
                    // print cards
                    PrintPlayerCardDeck(socket);
                    
                    // Let the user pick a card
                    networkServices->WriteToClient("Choose the card you want to remove from the deck\n", socket, true);
                    std::string card_name = Utils::ToLowerCase(networkServices->PromptClient(socket));
                    
                    // Check if this card exists
                    card_removed = CheckCard(card_name);
                    if (!card_removed)
                        networkServices->WriteToClient("This is not a valid card", socket);
                }
            }
            
            // Shuffle the deck
            player_card_deck.Shuffle();
        }
    }
}

void GameManager::StartRound()
{
	for (int x = 0; x < number_of_player_cards; x++)
	{
		for (int y = 0; y < players.size(); y++)
		{
			std::shared_ptr<Player> player = players.at(y);
			if (player->ContainsPlayerCard(PlayerCardType(x)))
			{
				// Let the player do his turn
			}
		}
	}
}

void GameManager::Turn(std::shared_ptr<Player> player)
{

}

void GameManager::EndGame()
{

}

bool GameManager::CheckCard(std::string card_name, std::shared_ptr<Player> player)
{
	if (card_name == "builder") {
		AddOrRemoveCard(PlayerCardType::BUILDER, player);
		return true;
	} else if (card_name == "condottiere") {
		AddOrRemoveCard(PlayerCardType::CONDOTTIERE, player);
		return true;
	} else if (card_name == "king") {
		AddOrRemoveCard(PlayerCardType::KING, player);
		return true;
	} else if (card_name == "magician") {
		AddOrRemoveCard(PlayerCardType::MAGICIAN, player);
		return true;
	} else if (card_name == "merchant") {
		AddOrRemoveCard(PlayerCardType::MERCHANT, player);
		return true;
	} else if (card_name == "murderer") {
		AddOrRemoveCard(PlayerCardType::MURDERER, player);
		return true;
	} else if (card_name == "preacher") {
		AddOrRemoveCard(PlayerCardType::PREACHER, player);
		return true;
	} else if (card_name == "thief") {
		AddOrRemoveCard(PlayerCardType::THIEF, player);
		return true;
	} else {
		return false;
	}
}

void GameManager::AddOrRemoveCard(PlayerCardType type, std::shared_ptr<Player> player)
{
	if (player != nullptr)
		AddCard(type, player);
	else
		RemoveCard(type);
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

void GameManager::RemoveCard(PlayerCardType type)
{
	for (int i = 0; i < player_card_deck.Size(); i++)
	{
		if (player_card_deck.Get(i)->GetType() == type)
		{
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

void GameManager::PrintPlayerCardDeck(std::shared_ptr<Socket> socket)
{
	std::string availableCards = "Available cards:\n\n";
	for (int i = 0; i < player_card_deck.Size(); i++)
	{
		availableCards.append(player_card_deck.Get(i)->GetName() + "\n");
	}
	availableCards.append("\n");
	networkServices->WriteToClient(availableCards, socket);
}

GameManager::~GameManager()
{
}