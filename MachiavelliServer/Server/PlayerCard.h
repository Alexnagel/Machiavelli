#pragma once

#include "Card.h"
#include "PlayerCardType.h"

class PlayerCard : public Card
{
public:
	PlayerCard(std::string name);
	virtual ~PlayerCard();

	virtual std::string GetName();
	virtual std::string GetCharacteristicDescription();
	virtual void PerformCharacteristic();
	virtual PlayerCardType GetType();
};

