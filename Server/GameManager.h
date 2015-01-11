#pragma once

#include <thread>
#include <exception>
#include <memory>
#include <iostream>
#include <vector>

#include "Deck.h"
#include "Parser.h"
#include "Player.h"
#include "PlayerCard.h"
#include "BuildCard.h"

class NetworkServices;
class GameManager
{
private:
	// Variables
    std::unique_ptr<NetworkServices> networkServices;
	std::vector<std::shared_ptr<Player>> players;
	Deck<std::shared_ptr<PlayerCard>> player_card_deck;
	Deck<std::shared_ptr<BuildCard>> building_card_deck;

	// Functions
	void GetPlayerCard(std::shared_ptr<Player> player);

public:
	GameManager();
	~GameManager();

    // Functions
    void Start();
    
	// Getters
	std::shared_ptr<Player> GetPlayer(int i) const;
    int GetPlayerAmount() const;
    
	// Setters
    std::shared_ptr<Player> AddPlayer(std::string name, std::shared_ptr<Socket> socket);
};

