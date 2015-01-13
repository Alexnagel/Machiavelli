#include "PlayerCard.h"


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

void PlayerCard::PerformCharacteristic()
{

}

PlayerCardType PlayerCard::GetType()
{
	return PlayerCardType::NONE;
}