#pragma once
#include "Card.h"
class PlayerCard : public Card
{
public:
	PlayerCard(std::string name);
	virtual ~PlayerCard();

	virtual void PerformCharacteristic() = 0;
};

