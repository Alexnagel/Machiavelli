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

std::shared_ptr<Socket> Player::GetSocket()
{
	return socket;
}

std::shared_ptr<PlayerCard> Player::GetCurrentPlayerCard()
{
	return current_player_card;
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

std::vector<std::shared_ptr<PlayerCard>> Player::GetPlayerCards()
{
	return player_card_collection;
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
void Player::SetCurrentPlayerCard(std::shared_ptr<PlayerCard> player_card)
{
	this->current_player_card = player_card;
}

void Player::AddPlayerCard(std::shared_ptr<PlayerCard> player_card)
{
	player_card_collection.push_back(player_card);
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

void Player::RemoveGold(int gold)
{
	this->gold -= gold;
}

void Player::AddPoints(int points)
{
	this->points += points;
}

void Player::SetSocket(std::shared_ptr<Socket> socket)
{
	this->socket = socket;
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

bool Player::ContainsPlayerCard(PlayerCardType type)
{
	for (int i = 0; i < player_card_collection.size(); i++)
	{
		if (player_card_collection.at(i)->GetType() == type)
		{
			SetCurrentPlayerCard(player_card_collection.at(i));
			return true;
		}
	}
    return false;
}