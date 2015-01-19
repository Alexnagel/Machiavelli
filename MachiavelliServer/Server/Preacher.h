#pragma once
#include "PlayerCard.h"
class Preacher :
	public PlayerCard
{
public:
	Preacher();
	~Preacher();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	PlayerCardType GetType();
};

