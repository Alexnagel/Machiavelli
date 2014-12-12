#include "BuildCard.h"


BuildCard::BuildCard(std::string name, int cost, CardColor color) : Card(name), cost(cost), color(color)
{
}


BuildCard::~BuildCard()
{
}


std::string BuildCard::GetName()
{
	return name;
}


int BuildCard::GetCost()
{
	return cost;
}


CardColor BuildCard::GetColor()
{
	return color;
}