#pragma once

#include "Card.h"
#include "CardColor.h"

class BuildCard : public Card
{
private:
	int cost;
	std::string description;
	CardColor color;

public:
	BuildCard(std::string name, int cost, CardColor color, std::string description = "");
	~BuildCard();

	// Getters
	std::string GetName();
	int GetCost();
	CardColor GetColor();
    std::string GetColorString();
};