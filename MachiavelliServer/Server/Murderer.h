#pragma once

#include "PlayerCard.h"

class Murderer :
	public PlayerCard
{
public:
	Murderer();
	~Murderer();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic();
	PlayerCardType GetType();
};

