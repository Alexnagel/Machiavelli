#include "BuildCard.h"
#include "Player.h"
#include "GameManager.h"

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

std::string BuildCard::GetCardString()
{
    return name + " (" + std::to_string(cost) + ", " + GetColorString() + ")";
}

void BuildCard::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
}

BuildingEnum BuildCard::GetBuildingType()
{
    return BuildingEnum::NORMAL;
}