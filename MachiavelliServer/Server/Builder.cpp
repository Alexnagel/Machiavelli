#include "Builder.h"


Builder::Builder() : PlayerCard("Builder")
{
}


Builder::~Builder()
{
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