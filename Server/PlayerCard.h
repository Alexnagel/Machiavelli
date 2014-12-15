#pragma once
#include "Card.h"
class PlayerCard : public Card
{
public:
	PlayerCard(std::string name);
	virtual ~PlayerCard();

	virtual std::string GetName();
	virtual void PerformCharacteristic();
};

