#pragma once
#include "PlayerCard.h"
class Merchant :
	public PlayerCard
{
public:
	Merchant();
	~Merchant();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	PlayerCardType GetType();
};

