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
#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "ServerSocket.h"

class GameManager
{
private:
	// Variables
	std::vector<std::shared_ptr<Player>> players;
	Deck<std::shared_ptr<PlayerCard>> player_card_deck;
	Deck<std::shared_ptr<BuildCard>> building_card_deck;

	// Server functions
	void ConsumeCommand();
	void HandleClient(Socket* socket);

	// Functions
	void Start();
	void GetPlayerCard(std::shared_ptr<Player> player);

public:
	GameManager();
	~GameManager();

	// Getters
	std::shared_ptr<Player> GetPlayer(int i) const;
	
	// Setters
	void AddPlayer(std::string name);
};

