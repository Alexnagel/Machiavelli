#include "Merchant.h"
#include "CardColor.h"
#include "NetworkServices.h"

Merchant::Merchant() : PlayerCard("Merchant")
{
}


Merchant::~Merchant()
{
}

std::string Merchant::GetCharacteristicDescription()
{
	return "As a Merchant you will receive 1 gold for every green building you have build.";
}

void Merchant::PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
	std::shared_ptr<Socket> socket = player->GetSocket();
	std::vector<std::shared_ptr<BuildCard>> builded_cards_list = player->GetBuildedBuildings();

	int counter = 0;
	for (int i = 0; i < builded_cards_list.size(); i++)
	{
		std::shared_ptr<BuildCard> build_card = builded_cards_list.at(i);
		if (build_card->GetColor() == CardColor::GREEN)
		{
			player->AddGold(1);
			counter++;
		}
	}

	std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();
	networkServices->WriteToClient("You received " + std::to_string(counter) + " gold.", socket, true);

	// Set used characteristic on true
	player->SetUsedCharacteristic(true);

	// Let the other players know what happend
	networkServices->WriteToAllClients(player->GetName() + " received " + std::to_string(counter) + " gold.");
}

PlayerCardType Merchant::GetType()
{
	return PlayerCardType::MERCHANT;
}