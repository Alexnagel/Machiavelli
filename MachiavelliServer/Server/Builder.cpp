#include "Builder.h"


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
	
}

PlayerCardType Builder::GetType()
{
	return PlayerCardType::BUILDER;
}