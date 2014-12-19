#pragma once

#include <iostream>
#include <vector>

#include "Deck.h"
#include "Parser.h"
#include "Player.h"
#include "PlayerCard.h"
#include "BuildCard.h"

class GameManager
{
private:
	// Variables
	std::vector<Player> players;
	//Deck<PlayerCard> player_card_deck;
	//Deck<BuildCard> building_card_deck;

	// Functions


public:
	GameManager();
	~GameManager();

	// Functions
	Player GetPlayer(int i);
};

