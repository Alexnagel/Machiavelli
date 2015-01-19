#include "PlayerCard.h"
#include "GameManager.h"
#include "Player.h"

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

PlayerCardType PlayerCard::GetType()
{
	return PlayerCardType::NONE;
}