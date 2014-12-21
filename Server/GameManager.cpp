#include "GameManager.h"


GameManager::GameManager()
{
	// Init decks
	building_card_deck = Parser::LoadBuildingFile();
	player_card_deck = Parser::LoadCharacterFile();
}


GameManager::~GameManager()
{
}

void GameManager::Start()
{

}

Player GameManager::GetPlayer(int i) const
{
	if (players.size() > i)
		return players.at(i);
	else
		return Player();
}

void GameManager::AddPlayer()
{
	players.push_back(Player());
}