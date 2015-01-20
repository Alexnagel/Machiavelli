#include "BuildCard.h"


BuildCard::BuildCard(std::string name, int cost, CardColor color, std::string description) : Card(name), cost(cost), color(color), description(description)
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

std::string BuildCard::GetColorString()
{
    switch (color) {
        case CardColor::BLUE :
            return "Blue";
            break;
        case CardColor::GREEN:
            return "Green";
            break;
        case CardColor::PURPLE:
            return "Purple";
            break;
        case CardColor::RED:
            return "Red";
            break;
        case CardColor::YELLOW:
            return "Yellow";
            break;
        default:
            return "blue";
            break;
    }
}