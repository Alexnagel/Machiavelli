#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "Deck.h"
#include "BuildCard.h"
#include "PlayerCard.h"

#include "HauntedCity.h"
#include "Keep.h"
#include "Graveyard.h"
#include "Laboratory.h"
#include "Smithy.h"
#include "Observatory.h"
#include "Library.h"
#include "SchoolOfMagic.h"
#include "DragonGate.h"
#include "University.h"

#include "Builder.h"
#include "Condottiere.h"
#include "King.h"
#include "Magician.h"
#include "Merchant.h"
#include "Murderer.h"
#include "Preacher.h"
#include "Thief.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#if defined(__APPLE__) || defined(__linux__)
    #include <unistd.h>
    #define GetCurrentDir getcwd
#else
    #include <direct.h>
    #define GetCurrentDir _getcwd
#endif

class Parser
{
private:
	static CardColor GetColor(std::string color);
	static std::shared_ptr<PlayerCard> GetPlayerCard(std::string player);
    
    static std::string CurrentPath();
    static std::shared_ptr<BuildCard> GetSpecialCard(std::string name);

public:
	Parser();
	~Parser();

	static Deck<std::shared_ptr<BuildCard>> LoadBuildingFile();
	static Deck<std::shared_ptr<PlayerCard>> LoadCharacterFile();
};