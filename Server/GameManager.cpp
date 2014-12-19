#include "GameManager.h"


GameManager::GameManager()
{
	// Init decks
	Parser::LoadBuildingFile();
	Parser::LoadCharacterFile();
}


GameManager::~GameManager()
{
}

