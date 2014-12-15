#include "Parser.h"


Parser::Parser()
{
}


Parser::~Parser()
{
}

std::vector<BuildCard> Parser::LoadBuildingFile()
{
	std::vector<BuildCard> build_cards;
	std::string line, name, color, description;
	int price;

	std::ifstream file("C://Users//Sjoerd//Documents//Bouwkaarten.csv");
	while (std::getline(file, line))
	{
		try
		{
			int position;
			int counter = 0;
			while ((position = line.find(";")) != std::string::npos || (position = line.find(",")) != std::string::npos)
			{
				switch (counter)
				{
				case 0: name = line.substr(0, position); break;
				case 1: price = atoi(line.substr(0, position).c_str()); break;
				case 2: color = line.substr(0, position); break;
				case 3: description = line.substr(0, position); break;
				}

				// Remove the text that is added into a variable
				line.erase(0, position + 1);

				// Raise the counter
				counter++;
			}

			// Add the buildcard
			if (description.empty())
				build_cards.push_back(BuildCard(name, price, GetColor(color)));
			else
				build_cards.push_back(BuildCard(name, price, GetColor(color), description));
		}
		catch (...){}
	}

	// Return the cards
	return build_cards;
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

std::vector<PlayerCard> Parser::LoadCharacterFile()
{
	std::vector<PlayerCard> player_cards;
	std::string line, player;
	int nr;

	std::ifstream file("C://Users//Sjoerd//Documents//karakterkaarten.csv");
	while (std::getline(file, line))
	{
		try 
		{
			int position;
			while ((position = line.find(";")) != std::string::npos || (position = line.find(",")) != std::string::npos)
			{
				nr = atoi(line.substr(0, position).c_str());
				player = line.substr(position + 1, line.length());

				// Remove the text that is added into a variable
				line = "";
			}

			// Add the player card
			player_cards.push_back(GetPlayerCard(player));
		}
		catch (...){}
	}

	// Return the cards
	return player_cards;
}

PlayerCard Parser::GetPlayerCard(std::string player)
{
	if (player == "Moordenaar")
		return Murderer();
	else if (player == "Dief")
		return Thief();
	else if (player == "Magiër")
		return Magician();
	else if (player == "Koning")
		return King();
	else if (player == "Prediker")
		return Preacher();
	else if (player == "Koopman")
		return Merchant();
	else if (player == "Bouwmeester")
		return Builder();
	else if (player == "Condottiere")
		return Condottiere();
	else
		return PlayerCard("");
}