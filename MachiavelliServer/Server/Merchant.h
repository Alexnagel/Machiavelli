#pragma once
#include "PlayerCard.h"
class Merchant :
	public PlayerCard
{
public:
	Merchant();
	~Merchant();

	void PerformCharacteristic();
	PlayerCardType GetType();
};

