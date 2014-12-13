#include "Parser.h"


Parser::Parser()
{
}


Parser::~Parser()
{
}

void Parser::LoadBuildingFile(std::ifstream file)
{
	std::vector<BuildCard> buildcards;
	std::string line, name, color, description;
	int price;

	//std::ifstream file("H://Internet Downloads//Bouwkaarten.csv");
	while (std::getline(file, line))
	{
		int position;
		while ((position = line.find(";")) != std::string::npos || (position = line.find(",")) != std::string::npos)
		{
			std::cout << line.substr(0, position) << std::endl;
			line.erase(0, position + 1);
		}
		/*std::istringstream iss(line);
		if (!(iss >> name >> price >> color))
		{
		buildcards.push_back(BuildCard(name, price, GetColor(color)));
		}
		else if (!(iss >> name >> price >> color >> description))
		{
		buildcards.push_back(BuildCard(name, price, GetColor(color)));
		}*/
	}
}

CardColor Parser::GetColor(std::string color)
{
	if (color == "geel")
		return CardColor::YELLOW;
	else if (color == "groen")
		return CardColor::GREEN;
	else if (color == "blauw")
		return CardColor::BLUE;
	else if (color == "rood")
		return CardColor::RED;
	else if (color == "lila")
		return CardColor::PURPLE;
}

void Parser::LoadCharacterFile(std::ifstream file)
{
}