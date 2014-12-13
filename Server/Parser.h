#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "BuildCard.h"

class Parser
{
private:
	static CardColor GetColor(std::string color);

public:
	Parser();
	~Parser();

	static void LoadBuildingFile(std::ifstream file);
	static void LoadCharacterFile(std::ifstream file);
};