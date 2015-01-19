#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Socket.h"
#include "BuildCard.h"
#include "PlayerCard.h"
#include "TurnEnum.h"

class Player
{
private:
	std::shared_ptr<Socket> socket;
	std::string name;
	std::vector<std::shared_ptr<BuildCard>> builded_buildings;
	std::vector<std::shared_ptr<BuildCard>> build_card_collection;
	std::vector<std::shared_ptr<PlayerCard>> player_card_collection;
	std::shared_ptr<PlayerCard> current_player_card;
	int gold;
	int points;

public:
	Player(std::string name);
	~Player();

	// Getters
	std::string GetName();
	std::shared_ptr<Socket> GetSocket();
	std::shared_ptr<PlayerCard> GetCurrentPlayerCard();
	std::shared_ptr<BuildCard> GetBuildCard(int index);
	std::vector<std::shared_ptr<BuildCard>> GetAllBuildCards();
	std::vector<std::shared_ptr<BuildCard>> GetBuildedBuildings();
	std::vector<std::shared_ptr<PlayerCard>> GetPlayerCards();
	int GetPoints();
	int GetGold();

	// Setters
	void SetCurrentPlayerCard(std::shared_ptr<PlayerCard> player_card);
	void AddPlayerCard(std::shared_ptr<PlayerCard> player_card);
	void AddBuildCard(std::shared_ptr<BuildCard> build_card);
	void AddBuildCards(std::vector<std::shared_ptr<BuildCard>> build_cards);
	void AddGold(int gold);
	void RemoveGold(int gold);
	void AddPoints(int points);
	void DestroyBuilding(std::shared_ptr<BuildCard> build_card);
	void SetSocket(std::shared_ptr<Socket> socket);

	// Functions
	void Turn(TurnEnum turn, std::shared_ptr<BuildCard> build_card = nullptr);
	bool ContainsPlayerCard(PlayerCardType type);
};

