#include "Player.h"


Player::Player(std::string name) : name(name), gold(2), points(0)
{
}


Player::~Player()
{
}


// Getters
std::string Player::GetName()
{
	return name;
}

std::shared_ptr<PlayerCard> Player::GetPlayerCard()
{
	return player_card;
}

std::shared_ptr<BuildCard> Player::GetBuildCard(int index)
{
	if (index < build_card_collection.size())
		return build_card_collection.at(index);
	else
		return nullptr;
}

std::vector<std::shared_ptr<BuildCard>> Player::GetAllBuildCards()
{
	return build_card_collection;
}

std::vector<std::shared_ptr<BuildCard>> Player::GetBuildedBuildings()
{
	return builded_buildings;
}

int Player::GetPoints()
{
	return points;
}

int Player::GetGold()
{
	return gold;
}


// Setters
void Player::SetPlayerCard(std::shared_ptr<PlayerCard> player_card)
{
	this->player_card = player_card;
}

void Player::AddBuildCard(std::shared_ptr<BuildCard> build_card)
{
	build_card_collection.push_back(build_card);
}

void Player::AddBuildCards(std::vector<std::shared_ptr<BuildCard>> build_cards)
{
	for (int i = 0; i < build_cards.size(); i++)
	{
		this->build_card_collection.push_back(build_cards.at(i));
	}
}

void Player::AddGold(int gold)
{
	this->gold += gold;
}

void Player::AddPoints(int points)
{
	this->points += points;
}


// Functions
void Player::Turn(TurnEnum turn, std::shared_ptr<BuildCard> build_card)
{
	switch (turn)
	{
	case TurnEnum::BUILD:
		break;
	case TurnEnum::BUILDCARD:
		break;
	case TurnEnum::GOLD:
		break;
	case TurnEnum::SPECIAL:
		break;
	case TurnEnum::PASS:
		break;
	}
}