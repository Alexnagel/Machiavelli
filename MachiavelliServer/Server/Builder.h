#pragma once
#include "PlayerCard.h"
class Builder :
	public PlayerCard
{
public:
	Builder();
	~Builder();

	void PerformCharacteristic();
	PlayerCardType GetType();
};

