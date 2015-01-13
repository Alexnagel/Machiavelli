#pragma once
#include "PlayerCard.h"
class Builder :
	public PlayerCard
{
public:
	Builder();
	~Builder();

	std::string GetCharacteristicDescription();
	void PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	PlayerCardType GetType();
};

