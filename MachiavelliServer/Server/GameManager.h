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
#include "PlayerCardType.h"

class NetworkServices;
class GameManager
{
private:
	// Variables
    std::shared_ptr<NetworkServices> networkServices;
	std::vector<std::shared_ptr<Player>> players;
	Deck<std::shared_ptr<PlayerCard>> player_card_deck;
	Deck<std::shared_ptr<BuildCard>> building_card_deck;
	PlayerCardType killed_player;
	PlayerCardType robbed_player;
	int index_king;
	int number_of_player_cards;
    int current_round;
    
	std::vector<std::string> player_card_names = {
		"Builder",
		"Condottiere",
		"King",
		"Magician",
		"Merchant",
		"Murderer",
		"Preacher",
		"Thief"
	};

	// Functions
	void GetPlayerCard();
	void StartRound();
	void Turn(std::shared_ptr<Player> player);
	void EndGame();
    
    // Turn functions
    void ShowPlayerOptions(std::shared_ptr<Player> player);
	void AddCard(PlayerCardType type, std::shared_ptr<Player> player);
	void RemoveCard(PlayerCardType type);
	void PrintPlayerCardDeck(std::shared_ptr<Socket> socket);

public:
	GameManager();
	~GameManager();

    // Functions
    void Start(std::shared_ptr<Player> player_called_start);
    
	// Getters
	std::shared_ptr<Player> GetPlayer(int i) const;
    int GetPlayerAmount() const;
	std::shared_ptr<NetworkServices> GetNetworkServices() const;
	std::vector<std::string> GetPlayerCardNames() const;
	PlayerCardType CheckCardType(std::string card_name) const;

	// Setters
    std::shared_ptr<Player> AddPlayer(std::string name, std::shared_ptr<Socket> socket);
	void SetKilledPlayer(PlayerCardType type);
	void SetRobbedPlayer(PlayerCardType type);
};

