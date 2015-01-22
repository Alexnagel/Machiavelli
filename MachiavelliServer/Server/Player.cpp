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

bool Player::HasUsedCharacteristic()
{
    return used_characteristic;
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

void Player::SetUsedCharacteristic(bool used)
{
    used_characteristic = used;
}

void Player::SetBuildCards(std::vector<std::shared_ptr<BuildCard>> build_cards)
{
	this->build_card_collection = build_cards;
}

std::string Player::GetPlayerInfo()
{
    std::string player_info;
    
    player_info.append("You are now playing as: " + current_player_card->GetName() + "\n");
    player_info.append("Gold:                   " + std::to_string(gold) + "\n\n");
    player_info.append("Buildings:\n");

    if (builded_buildings.size() > 0)
    {
        // Show constructed buildings
        for (std::shared_ptr<BuildCard> buildCard : builded_buildings)
        {
            
            player_info.append("  " + buildCard->GetName() + " (" + buildCard->GetColorString() + " " + std::to_string(buildCard->GetCost()) + ") \n");
        }
    }
    else
        player_info.append("You have no constructed buildings\n");
    
    player_info.append("\n");
    player_info.append("Cards in hand:\n");
    
    // Show player cards
    if (build_card_collection.size() > 0)
    {
        for (std::shared_ptr<BuildCard> buildCard : build_card_collection)
        {
            player_info.append("  " + buildCard->GetName() + " (" + buildCard->GetColorString() + " " + std::to_string(buildCard->GetCost()) + ") \n");
        }
    }
    else
        player_info.append("  You have no cards in your hand \n");
    
    player_info.append("\n");
    
    return player_info;
}

int Player::GetSpecialIndex(BuildingEnum buildingType)
{
    for (int i = 0; i < build_card_collection.size(); i++)
    {
        if (build_card_collection[i]->GetBuildingType() == buildingType)
            return i;
    }
    return -1;
}

void Player::RemoveBuildCard(int index)
{
	if (index < build_card_collection.size())
		build_card_collection.erase(build_card_collection.begin() + index);
}

void Player::ClearPlayerCards()
{
	player_card_collection.clear();
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

bool Player::ContainsPlayerCard(PlayerCardType type, bool set_card)
{
	for (int i = 0; i < player_card_collection.size(); i++)
	{
		if (player_card_collection.at(i)->GetType() == type)
		{
			if (set_card)
				SetCurrentPlayerCard(player_card_collection.at(i));
			return true;
		}
	}
    return false;
}

bool Player::ConstructBuilding(std::shared_ptr<BuildCard> build_card)
{
    if (gold >= build_card->GetCost())
    {
        gold -= build_card->GetCost();
        
        // Find the card to remove from available build cards
        auto itr = std::find(build_card_collection.begin(), build_card_collection.end(), build_card);
        build_card_collection.erase(itr);
        
        // Add to the constructed buildings
        builded_buildings.push_back(build_card);
        
        return true;
    }
    else
        return false;
}

void Player::DestroyBuilding(std::shared_ptr<BuildCard> build_card)
{
    auto itr = std::find(builded_buildings.begin(), builded_buildings.end(), build_card);
    if (itr != builded_buildings.end())
        builded_buildings.erase(itr);
}
