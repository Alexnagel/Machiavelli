#pragma once
#include "PlayerCard.h"
class Condottiere :
	public PlayerCard
{
public:
	Condottiere();
	~Condottiere();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic();
	PlayerCardType GetType();
};

