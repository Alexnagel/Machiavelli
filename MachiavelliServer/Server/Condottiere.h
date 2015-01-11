#pragma once
#include "PlayerCard.h"
class Condottiere :
	public PlayerCard
{
public:
	Condottiere();
	~Condottiere();

	void PerformCharacteristic();
	PlayerCardType GetType();
};

