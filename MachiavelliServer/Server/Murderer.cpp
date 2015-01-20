#include "Murderer.h"
#include "NetworkServices.h"

Murderer::Murderer() : PlayerCard("Murderer")
{
}


Murderer::~Murderer()
{
}

std::string Murderer::GetCharacteristicDescription()
{
	return "As a Murderer you choose a player you will kill.";
}

void Murderer::PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
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

	player_options.append("Choose the person you want to kill: \n");

	std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();
	networkServices->WriteToClient(player_options, socket, true);

	bool player_killed = false;
	while (!player_killed)
	{
		card_name = networkServices->PromptClient(socket);

		PlayerCardType card_type = manager->CheckCardType(card_name);
		if (card_type != PlayerCardType::NONE)
		{
			manager->SetKilledPlayer(card_type);
			player_killed = true;
		}
		else
			networkServices->WriteToClient("This card doesn't exist.", socket, true);
	}

	// Set used characteristic on true
	player->SetUsedCharacteristic(true);

	// Let all other players know which player is killed
	networkServices->WriteToAllClients("The " + card_name + " is killed.");
}

PlayerCardType Murderer::GetType()
{
	return PlayerCardType::MURDERER;
}