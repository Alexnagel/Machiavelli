#include "BuildCard.h"
#include "Player.h"
#include "GameManager.h"

BuildCard::BuildCard(std::string name, int cost, CardColor color, std::string description) : Card(name), cost(cost), color(color), description(description), turn_based_card(false), end_game_card(false), card_used(false)
{
}

BuildCard::BuildCard(std::string name, int cost, CardColor color, std::string description, bool turn_based, bool end_game) : Card(name), cost(cost), color(color), description(description), turn_based_card(turn_based), end_game_card(end_game), card_used(false)
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

bool BuildCard::IsCardEndGame()
{
    return end_game_card;
}

bool BuildCard::IsCardTurnBased()
{
    return turn_based_card;
}

bool BuildCard::IsCardUsed()
{
    return card_used;
}

BuildingEnum BuildCard::GetBuildingType()
{
    return BuildingEnum::NORMAL;
}