#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Deck.h"
#include "BuildCard.h"
#include "PlayerCard.h"
#include "Builder.h"
#include "Condottiere.h"
#include "King.h"
#include "Magician.h"
#include "Merchant.h"
#include "Murderer.h"
#include "Preacher.h"
#include "Thief.h"

class Parser
{
private:
	static CardColor GetColor(std::string color);
	static PlayerCard GetPlayerCard(std::string player);

public:
	Parser();
	~Parser();

	static Deck<BuildCard> LoadBuildingFile();
	static Deck<PlayerCard> LoadCharacterFile();
};