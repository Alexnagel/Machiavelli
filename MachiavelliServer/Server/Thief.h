#pragma once
#include "PlayerCard.h"
class Thief :
	public PlayerCard
{
public:
	Thief();
	~Thief();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic();
	PlayerCardType GetType();
};

