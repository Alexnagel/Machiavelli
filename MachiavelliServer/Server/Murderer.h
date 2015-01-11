#pragma once

#include "PlayerCard.h"

class Murderer :
	public PlayerCard
{
public:
	Murderer();
	~Murderer();

	void PerformCharacteristic();
	PlayerCardType GetType();
};

