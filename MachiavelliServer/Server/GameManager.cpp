#include "GameManager.h"
#include "NetworkServices.h"

GameManager::GameManager() : index_king(0)
{
	networkServices = std::make_shared<NetworkServices>(std::unique_ptr<GameManager>(this));
		//std::unique_ptr<NetworkServices>(new NetworkServices(std::unique_ptr<GameManager>(this)));
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

void GameManager::Start(std::shared_ptr<Player> player_called_start)
{
	// Init decks
	building_card_deck = Parser::LoadBuildingFile();
	player_card_deck = Parser::LoadCharacterFile();

	// Set the number of player cards
	number_of_player_cards = player_card_deck.Size();

	// Shuffle the decks
	player_card_deck.Shuffle();
	building_card_deck.Shuffle();
		
    // Send message of starting game
	networkServices->WriteToAllClients("\n");
    networkServices->WriteToAllClients("Starting the game!\n");
    
	// Let the player choose a card
	GetPlayerCard();

    // Set the round
    current_round = 1;
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
				PlayerCardType card_type = CheckCardType(card_name);
				if (card_type != PlayerCardType::NONE)
				{
					AddCard(card_type, player);
					card_set = true;
					networkServices->WriteToClient("You have chosen: " + card_name + "\n", socket);
				}
				else
					networkServices->WriteToClient("This is not a valid card \n", socket);
            }
            
            // Let the player remove a card from the deck
            if ((i != index_king || (i == index_king && t != 0)) && i < 3)
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
					PlayerCardType card_type = CheckCardType(card_name);
					if (card_type != PlayerCardType::NONE)
					{
						RemoveCard(card_type);
						card_removed = true;
					}
					else
                        networkServices->WriteToClient("This is not a valid card \n", socket);
                }
            }
            
            // remove the last card, no need in letting the player do it
            if (i > 3)
            {
                player_card_deck.RemoveLast();
                networkServices->WriteToClient("Removed last card", socket);
            }
            else
            {
                // Else write that the other player is picking cards
                networkServices->WriteToClient("The other player is picking cards\n", socket);
                // Shuffle the deck
                player_card_deck.Shuffle();
            }
        }
    }
    
    // Write to all clients the cards have been picked
    networkServices->WriteToAllClients("The character cards have been picked.\n");
}

void GameManager::StartRound()
{
    networkServices->WriteToAllClients("\n\nStarting round " + std::to_string(current_round) + "\n");
	for (int x = 0; x < number_of_player_cards; x++)
	{
		for (int y = 0; y < players.size(); y++)
		{
			std::shared_ptr<Player> player = players.at(y);
			if (player->ContainsPlayerCard(PlayerCardType(x)))
			{
                networkServices->WriteToAllClients("It's " + player->GetName() + "'s turn \n");
                Turn(player);
			}
		}
	}
    networkServices->WriteToAllClients("\n Round " + std::to_string(current_round) + " is finished\n");
    current_round++;
}

void GameManager::Turn(std::shared_ptr<Player> player)
{
    std::shared_ptr<Socket> socket = player->GetSocket();
    networkServices->WriteToClient("<line>", socket);
    
    ShowPlayerOptions(player);
}

void GameManager::ShowPlayerOptions(std::shared_ptr<Player> player)
{
    std::shared_ptr<Socket> socket = player->GetSocket();
    
    bool option_chosen = false;
    while (!option_chosen)
    {
        std::string player_options;
        player_options.append("It's your turn, you have the following options to choose from: \n");
        player_options.append("\t 1: Receive two gold \n");
        player_options.append("\t 2: Take building cards \n");
        player_options.append("Please choose one of the given options \n");
        networkServices->WriteToClient(player_options, socket, true);
        
        std::string chosen_option = networkServices->PromptClient(socket);
        if (chosen_option == "1")
        {
            // Add the two gold
            player->AddGold(2);
            
            networkServices->WriteToClient("You have chosen to receive two gold. You now have " + std::to_string(player->GetGold()) + " gold.\n", socket);
            option_chosen = true;
        }
        else if (chosen_option == "2")
        {
            option_chosen = true;
        }
		else if (chosen_option == "3")
		{
			option_chosen = true;
		}
        else
            networkServices->WriteToClient("\n This isn't a valid option, please try again \n", socket);
    }
}

void GameManager::EndGame()
{

}

PlayerCardType GameManager::CheckCardType(std::string card_name) const
{
	if (card_name == "builder")
		return PlayerCardType::BUILDER;
	else if (card_name == "condottiere")
		return PlayerCardType::CONDOTTIERE;
	else if (card_name == "king")
		return PlayerCardType::KING;
	else if (card_name == "magician")
		return PlayerCardType::MAGICIAN;
	else if (card_name == "merchant")
		return PlayerCardType::MERCHANT;
	else if (card_name == "murderer")
		return PlayerCardType::MURDERER;
	else if (card_name == "preacher")
		return PlayerCardType::PREACHER;
	else if (card_name == "thief")
		return PlayerCardType::THIEF;
	else
		return PlayerCardType::NONE;
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

std::shared_ptr<NetworkServices> GameManager::GetNetworkServices() const
{
	return networkServices;
}

std::vector<std::string> GameManager::GetPlayerCardNames() const
{
	return player_card_names;
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

void GameManager::SetKilledPlayer(PlayerCardType type)
{
	killed_player = type;
}

void GameManager::SetRobbedPlayer(PlayerCardType type)
{
	robbed_player = type;
}

GameManager::~GameManager()
{
}