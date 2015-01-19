#pragma once
#include "PlayerCard.h"
class Condottiere :
	public PlayerCard
{
public:
	Condottiere();
	~Condottiere();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	PlayerCardType GetType();
};

