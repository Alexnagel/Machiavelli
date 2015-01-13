#pragma once
#include "PlayerCard.h"
class Magician :
	public PlayerCard
{
public:
	Magician();
	~Magician();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic();
	PlayerCardType GetType();
};

