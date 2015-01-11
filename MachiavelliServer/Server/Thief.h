#pragma once
#include "PlayerCard.h"
class Thief :
	public PlayerCard
{
public:
	Thief();
	~Thief();

	void PerformCharacteristic();
	PlayerCardType GetType();
};

