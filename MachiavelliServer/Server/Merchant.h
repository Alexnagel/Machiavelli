#pragma once
#include "PlayerCard.h"
class Merchant :
	public PlayerCard
{
public:
	Merchant();
	~Merchant();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic();
	PlayerCardType GetType();
};

