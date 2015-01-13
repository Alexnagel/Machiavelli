#pragma once
#include "PlayerCard.h"
class Builder :
	public PlayerCard
{
public:
	Builder();
	~Builder();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic();
	PlayerCardType GetType();
};

