#pragma once
#include "PlayerCard.h"
class Magician :
	public PlayerCard
{
public:
	Magician();
	~Magician();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	PlayerCardType GetType();
};

