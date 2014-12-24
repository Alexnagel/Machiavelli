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
	std::vector<std::shared_ptr<Player>> players;
	Deck<std::shared_ptr<PlayerCard>> player_card_deck;
	Deck<std::shared_ptr<BuildCard>> building_card_deck;

	// Functions


public:
	GameManager();
	~GameManager();

	// Functions
	void Start();

	// Getters
	std::shared_ptr<Player> GetPlayer(int i) const;
	
	// Setters
	void AddPlayer(std::string name);
};

