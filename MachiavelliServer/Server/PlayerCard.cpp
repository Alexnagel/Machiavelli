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

void PlayerCard::PerformCharacteristic()
{

}