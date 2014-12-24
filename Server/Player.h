#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "BuildCard.h"
#include "PlayerCard.h"
#include "TurnEnum.h"

class Player
{
private:
	std::string name;
	std::vector<std::shared_ptr<BuildCard>> builded_buildings;
	std::vector<std::shared_ptr<BuildCard>> build_card_collection;
	std::shared_ptr<PlayerCard> player_card;
	int gold;
	int points;

public:
	Player(std::string name);
	~Player();

	// Getters
	std::string GetName();
	std::shared_ptr<PlayerCard> GetPlayerCard();
	std::shared_ptr<BuildCard> GetBuildCard(int index);
	std::vector<std::shared_ptr<BuildCard>> GetAllBuildCards();
	std::vector<std::shared_ptr<BuildCard>> GetBuildedBuildings();
	int GetPoints();
	int GetGold();

	// Setters
	void SetPlayerCard(std::shared_ptr<PlayerCard> player_card);
	void AddBuildCard(std::shared_ptr<BuildCard> build_card);
	void AddBuildCards(std::vector<std::shared_ptr<BuildCard>> build_cards);
	void AddGold(int gold);
	void AddPoints(int points);
	void DestroyBuilding(std::shared_ptr<BuildCard> build_card);

	// Functions
	void Turn(TurnEnum turn, std::shared_ptr<BuildCard> build_card = nullptr);
};

