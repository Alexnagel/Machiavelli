#pragma once

#include "Card.h"
#include "CardColor.h"

class Player;
class GameManager;
class BuildCard : public Card
{
protected:
	int cost;
	std::string description;
	CardColor color;

    bool turn_based_card;
    bool end_game_card;
    bool card_used;
    
public:
	BuildCard(std::string name, int cost, CardColor color, std::string description = "");
    BuildCard(std::string name, int cost, CardColor color, std::string description, bool turn_based, bool end_game);
	virtual ~BuildCard();

	// Getters
    std::string GetName();
	int GetCost();
	CardColor GetColor();
    std::string GetColorString();
    std::string GetCardString();
    bool IsCardUsed();
    bool IsCardTurnBased();
    bool IsCardEndGame();
    
    virtual void UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
};