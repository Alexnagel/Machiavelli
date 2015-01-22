#include "Builder.h"
#include "NetworkServices.h"


Builder::Builder() : PlayerCard("Builder")
{
}


Builder::~Builder()
{
}

std::string Builder::GetCharacteristicDescription()
{
	return "As a builder you can take 2 buildcards and you are allowed to build 3 buildings";
}

void Builder::PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
	std::string output = "";
	std::shared_ptr<Player> chosen_player;
	std::shared_ptr<Socket> socket = player->GetSocket();
	std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();

	// Get 2 new cards
	std::vector<std::shared_ptr<BuildCard>> received_cards = manager->TakeCards(2);
	player->AddBuildCards(received_cards);

	// Show the cards
	ShowBuildCards(manager, player, received_cards);

	// Set used characteristic on true
	player->SetUsedCharacteristic(true);

	// Let all the other players know what happend
	output.clear();
	output.append(player->GetName() + " received 2 new cards.\n");
	networkServices->WriteToAllExceptCurrent(output, player);
}

PlayerCardType Builder::GetType()
{
	return PlayerCardType::BUILDER;
}