#include "GameManager.h"


GameManager::GameManager()
{
	// Init decks
	building_card_deck = Parser::LoadBuildingFile();
	player_card_deck = Parser::LoadCharacterFile();

	// Shuffle the decks
	player_card_deck.Shuffle();
	building_card_deck.Shuffle();
}


GameManager::~GameManager()
{
}

void GameManager::Start()
{

}

std::shared_ptr<Player> GameManager::GetPlayer(int i) const
{
	if (players.size() > i)
		return players.at(i);
	else
		return nullptr;
}

void GameManager::AddPlayer(std::string name)
{
	if (name.empty())
		name = "Player" + players.size();

	// Add the player
	players.push_back(std::make_shared<Player>(name));
}