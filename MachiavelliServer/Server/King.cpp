#include "King.h"
#include "CardColor.h"
#include "NetworkServices.h"

King::King() : PlayerCard("King")
{
}


King::~King()
{
}

std::string King::GetCharacteristicDescription()
{
	return "As the king you will earn 1 gold for every yellow building you have build.";
}

void King::PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
	std::shared_ptr<Socket> socket = player->GetSocket();
	std::vector<std::shared_ptr<BuildCard>> builded_cards_list = player->GetBuildedBuildings();

	int counter = 0;
	for (int i = 0; i < builded_cards_list.size(); i++)
	{
		std::shared_ptr<BuildCard> build_card = builded_cards_list.at(i);
		if (build_card->GetColor() == CardColor::YELLOW)
		{
			player->AddGold(1);
			counter++;
		}
	}

	std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();
	networkServices->WriteToClient("You received " + std::to_string(counter) + " gold.", socket, true);
}

PlayerCardType King::GetType()
{
	return PlayerCardType::KING;
}