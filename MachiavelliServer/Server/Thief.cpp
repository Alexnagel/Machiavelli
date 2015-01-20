#include "Thief.h"
#include "NetworkServices.h"

Thief::Thief() : PlayerCard("Thief")
{
}


Thief::~Thief()
{
}

std::string Thief::GetCharacteristicDescription()
{
	std::string output;

	output.append("As a Thief you will choose a character to steal all his gold.");
	output.append("You will receive the gold when it is this character his turn.");

	return output;
}

void Thief::PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
	std::string card_name;
	std::shared_ptr<Socket> socket = player->GetSocket();
	std::vector<std::string> player_card_names = manager->GetPlayerCardNames();

	std::string player_options;
	player_options.append("Options: \n\n");
	
	for (int i = 0; i < player_card_names.size(); i++)
	{
		player_options.append(player_card_names.at(i) + "\n");
	}

	player_options.append("Choose the person you want to steal from: \n");

	std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();
	networkServices->WriteToClient(player_options, socket, true);

	bool player_robbed = false;
	while (!player_robbed)
	{
		card_name = Utils::ToLowerCase(networkServices->PromptClient(socket));
		
		PlayerCardType card_type = manager->CheckCardType(card_name);
		if (card_type != PlayerCardType::NONE)
		{
			manager->SetRobbedPlayer(card_type);
			player_robbed = true;
		}
		else
			networkServices->WriteToClient("This card doesn't exist.", socket, true);
	}

	// Set used characteristic on true
	player->SetUsedCharacteristic(true);

	// Let all other players know which player is robbed
	networkServices->WriteToAllClients("The " + card_name + " is robbed.");
}

PlayerCardType Thief::GetType()
{
	return PlayerCardType::THIEF;
}