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

void Builder::PerformCharacteristic()
{
	/*
	Hij trekt 2 gebouwenkaarten. De bouwmeester mag in zijn beurt tot 3 gebouwenkaarten uitleggen. De
	bouwmeester kan derhalve aan het einde van het spel als enige meer dan 8 gebouwen bezitten.
	*/
}

PlayerCardType Builder::GetType()
{
	return PlayerCardType::BUILDER;
}