#pragma once

#include "Card.h"
#include "CardColor.h"

class BuildCard : public Card
{
private:
	int cost;
	CardColor color;

public:
	BuildCard(std::string name, int cost, CardColor color);
	~BuildCard();

	// Getters
	std::string GetName();
	int GetCost();
	CardColor GetColor();
};