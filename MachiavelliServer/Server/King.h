#pragma once
#include "PlayerCard.h"
class King :
	public PlayerCard
{
public:
	King();
	~King();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	PlayerCardType GetType();
};

