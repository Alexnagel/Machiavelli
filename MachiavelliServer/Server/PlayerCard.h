#pragma once

#include <memory>

#include "Card.h"
#include "PlayerCardType.h"

class GameManager;
class Player;
class PlayerCard : public Card
{
public:
	PlayerCard(std::string name);
	virtual ~PlayerCard();

	virtual std::string GetName();
	virtual std::string GetCharacteristicDescription();
	virtual void PerformCharacteristic(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	virtual void ShowBuildCards(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player, std::vector<std::shared_ptr<BuildCard>> cards);
	virtual PlayerCardType GetType();
};

