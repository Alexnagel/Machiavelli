#pragma once
#include "PlayerCard.h"
class Thief :
	public PlayerCard
{
public:
	Thief();
	~Thief();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	PlayerCardType GetType();
};

