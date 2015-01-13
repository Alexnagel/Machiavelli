#pragma once
#include "PlayerCard.h"
class King :
	public PlayerCard
{
public:
	King();
	~King();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic();
	PlayerCardType GetType();
};

