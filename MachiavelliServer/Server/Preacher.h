#pragma once
#include "PlayerCard.h"
class Preacher :
	public PlayerCard
{
public:
	Preacher();
	~Preacher();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic();
	PlayerCardType GetType();
};

