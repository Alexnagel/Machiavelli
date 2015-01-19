#pragma once

#include "PlayerCard.h"

class Murderer :
	public PlayerCard
{
public:
	Murderer();
	~Murderer();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	PlayerCardType GetType();
};

