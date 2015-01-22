#include "PlayerCard.h"
#include "GameManager.h"
#include "Player.h"
#include "NetworkServices.h"
#include "BuildCard.h"

PlayerCard::PlayerCard(std::string name) : Card(name)
{
}


PlayerCard::~PlayerCard()
{
}

std::string PlayerCard::GetName()
{
	return name;
}

std::string PlayerCard::GetCharacteristicDescription()
{
	return "";
}

void PlayerCard::PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{

}

void PlayerCard::ShowBuildCards(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player, std::vector<std::shared_ptr<BuildCard>> cards)
{
	std::string output = "";
	std::shared_ptr<Socket> socket = player->GetSocket();
	std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();

	output.append("\nReceived cards:\n");
	for (int i = 0; i < cards.size(); i++)
	{
		output.append("- Name: " + cards.at(i)->GetName() + ", Cost: " + std::to_string(cards.at(i)->GetCost()) + ", Color: " + cards.at(i)->GetColorString() + "\n");
	}

	networkServices->WriteToClient(output, socket, true);
}

PlayerCardType PlayerCard::GetType()
{
	return PlayerCardType::NONE;
}