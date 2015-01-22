#pragma once

#include <memory>

#include "Card.h"
#include "CardColor.h"
#include "BuildingEnum.h"

class Player;
class GameManager;
class BuildCard : public Card
{
protected:
	int cost;
	std::string description;
	CardColor color;
    
public:
	BuildCard(std::string name, int cost, CardColor color, std::string description = "");
	virtual ~BuildCard();

	// Getters
    std::string GetName();
	int GetCost();
	CardColor GetColor();
    std::string GetColorString();
    std::string GetCardString();
    
    virtual BuildingEnum GetBuildingType();
    virtual void UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
};