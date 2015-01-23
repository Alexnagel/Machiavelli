#include "Magician.h"
#include "NetworkServices.h"

Magician::Magician() : PlayerCard("Magician")
{
}


Magician::~Magician()
{
}

std::string Magician::GetCharacteristicDescription()
{
	std::string output;

	output.append("As a Magician you have two choices:\n");
	output.append("- You can change your building cards with another player (even if you have 0 cards).\n");
	output.append("- You can change you building cards with cards from the deck.");

	return output;
}


void Magician::PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
	std::string output = "";
	std::shared_ptr<Socket> socket = player->GetSocket();
	std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();

	// Print all the players
	output.append("As a magician you have two options: \n");
	output.append("1: You can trade your cards with another player.\n");
	output.append("2: Remove some cards from your hand and take the same amount from the deck.\n");
	output.append("Stop: Will stop the characteristic.\n\n");
	output.append("Please enter the number of the action you want to perform:\n");
	networkServices->WriteToClient(output, socket, true);

	// Choose a player
	output.clear();
	bool action_chosen = false;
	while (!action_chosen)
	{
		std::string input = Utils::ToLowerCase(networkServices->PromptClient(player));

		if (input == "1")
		{
			TradeCards(manager, player);
			action_chosen = true;
		}
		else if (input == "2")
		{
			ReplaceCards(manager, player);
			action_chosen = true;
		}
		else if (input == "stop")
		{
			return;
		}
		else
		{
			output.append("This isn't a valid option.\n");
			networkServices->WriteToClient(output, socket, true);
			action_chosen = false;
		}
	}

	// Set used characteristic on true
	player->SetUsedCharacteristic(true);
}

void Magician::TradeCards(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
	std::string output = "";
	std::shared_ptr<Player> chosen_player;
	std::shared_ptr<Socket> socket = player->GetSocket();
	std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();

	networkServices->WriteToClient("Players: \n", socket, true);
	std::vector<std::shared_ptr<Player>> players = manager->GetPlayers();
	for (int i = 0; i < players.size(); i++)
	{
		std::vector<std::shared_ptr<BuildCard>> build_cards = player->GetBuildedBuildings();
		if (players.at(i) != player)
		{
			output.append(std::to_string(i) + ": " + players.at(i)->GetName() + ", Cards: " + std::to_string(players.at(i)->GetAllBuildCards().size()) + "\n");
		}
	}
	output.append("Stop: Will stop the characteristic.\n\n");
	output.append("Choose the player where you want to chance cards with: \n");
	networkServices->WriteToClient(output, socket, true);

	// Choose a player
	output.clear();
	bool player_chosen = false;
	while (!player_chosen)
	{
		output.clear();
		std::string input = Utils::ToLowerCase(networkServices->PromptClient(player));

		if (input == "stop")
			return;

		try
		{
			int number = std::atoi(input.c_str());

			// Check if this number exists
			if (number < players.size())
			{
				player_chosen = true;
				chosen_player = players.at(number);
			}
			else
				output = "This is not a valid choice.\n";
		}
		catch (...)
		{
			output = "This is not a valid choice.\n";
		}
		networkServices->WriteToClient(output, socket, true);
	}
	output.append("\n");
	networkServices->WriteToClient(output, socket, true);
	
	// Change cards
	std::vector<std::shared_ptr<BuildCard>> temp = chosen_player->GetAllBuildCards();
	chosen_player->SetBuildCards(player->GetAllBuildCards());
	player->SetBuildCards(temp);

	// Show the cards
	ShowBuildCards(manager, player, player->GetAllBuildCards());
	ShowBuildCards(manager, chosen_player, chosen_player->GetAllBuildCards());

	// Let all the other players know what happend
	output.clear();
	output.append(player->GetName() + " changed cards with " + chosen_player->GetName() + ".\n");
	networkServices->WriteToAllClients(output);
}

void Magician::ReplaceCards(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
	std::string output = "";
	std::shared_ptr<Socket> socket = player->GetSocket();
	std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();

	// Choose cards you want to replace
	bool cards_chosen = false;
	std::vector<std::shared_ptr<BuildCard>> chosen_cards;
	while (!cards_chosen)
	{
		std::vector<std::shared_ptr<BuildCard>> cards = player->GetAllBuildCards();

		// Show the options
		output.clear();
		output.append("Choose the number of the card you want to remove from your deck: \n");
		for (int i = 0; i < cards.size(); i++)
		{
			output.append("   " + std::to_string(i) + ": " + cards[i]->GetCardString() + " \n");
		}
		output.append("   End: This will mean you are done chosing cards.\n");
		networkServices->WriteToClient(output, socket, true);

		// Choose a card
		output.clear();
		std::string input = Utils::ToLowerAndTrim(networkServices->PromptClient(player));
		if (input == "end")// && chosen_cards.size() > 0)
		{
			cards_chosen = true;
		}
		else
		{
			try
			{
				int number = std::atoi(input.c_str());

				// Check if this number exists
				if (number < cards.size())
				{
					chosen_cards.push_back(std::make_shared<BuildCard>(*cards.at(number)));
					player->RemoveBuildCard(number);
				}
				else
					output = "This is not a valid choice.\n";
			}
			catch (...)
			{
				output = "This is not a valid choice.\n";
			}
		}

		networkServices->WriteToClient(output, socket, true);
	}

	if (chosen_cards.size() > 0)
    {
        // Take new cards and add them to the players deck
        std::vector<std::shared_ptr<BuildCard>> received_cards = manager->TakeCards(chosen_cards.size());
        player->AddBuildCards(received_cards);
        
        // Add removed cards to the deck
        for (int i = 0; i < chosen_cards.size(); i++)
        {
            manager->AddBuildCard(chosen_cards.at(i));
        }
        
        // Show the cards
        ShowBuildCards(manager, player, received_cards);
    }

	// Let all the other players know what happend
	output.clear();
	output.append(player->GetName() + " Replaced " + std::to_string(chosen_cards.size()) + " of his cards with new cards.\n");
	networkServices->WriteToAllExceptCurrent(output, player);
    networkServices->WriteToAllClients("<line>\n");
}

PlayerCardType Magician::GetType()
{
	return PlayerCardType::MAGICIAN;
}