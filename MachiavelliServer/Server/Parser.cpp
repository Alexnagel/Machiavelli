#include "Parser.h"


Parser::Parser()
{
}


Parser::~Parser()
{
}

std::string Parser::CurrentPath()
{
    char cCurrentPath[FILENAME_MAX];
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
        return std::to_string(errno);
    
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    return std::string(cCurrentPath);
}

Deck<std::shared_ptr<BuildCard>> Parser::LoadBuildingFile()
{
	Deck<std::shared_ptr<BuildCard>> build_cards;
	std::string line, name, color, description;
	int price;

    std::string curPath = CurrentPath();
    std::ifstream file("/Users/Alex/School/Machiavelli/Build/Products/Debug/bouwkaarten.csv");
    //std::ifstream file("C://Users//Sjoerd Nijhof//Dropbox//C++//Machiavelli//Bouwkaarten.csv");
	//std::ifstream file("C://Users//Sjoerd//Dropbox//C++//Machiavelli//Bouwkaarten.csv");
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
				build_cards.Add(std::make_shared<BuildCard>(name, price, GetColor(color)));
			else
				build_cards.Add(std::make_shared<BuildCard>(name, price, GetColor(color), description));
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
    
    // Default value for xcode
    return CardColor::BLUE;
}

Deck<std::shared_ptr<PlayerCard>> Parser::LoadCharacterFile()
{
	Deck<std::shared_ptr<PlayerCard>> player_cards;
	std::string line, player;
	int nr;

    std::string curPath = CurrentPath();
	std::ifstream file("/Users/Alex/School/Machiavelli/Build/Products/Debug/karakterkaarten.csv");
	//std::ifstream file("C://Users//Sjoerd Nijhof//Dropbox//C++//Machiavelli//karakterkaarten.csv");
	//std::ifstream file("C://Users//Sjoerd//Dropbox//C++//Machiavelli//karakterkaarten.csv");
	while (std::getline(file, line))
	{
		try 
		{
			int position;
			while ((position = line.find(";")) != std::string::npos || (position = line.find(",")) != std::string::npos)
			{
				nr = atoi(line.substr(0, position).c_str());
				player = line.substr(position + 1, line.length());
                
                if (!player.empty() && player[player.size() - 1] == '\r')
                    player.erase(player.size() - 1);

				// Remove the text that is added into a variable
				line = "";
			}

			// Add the player card
			player_cards.Add(GetPlayerCard(player));
		}
		catch (...){}
	}

	// Return the cards
	return player_cards;
}

std::shared_ptr<PlayerCard> Parser::GetPlayerCard(std::string player)
{
	if (player == "Moordenaar")
		return std::make_shared<Murderer>();
	else if (player == "Dief")
		return std::make_shared<Thief>();
	else if (player == "Magier")
		return std::make_shared<Magician>();
	else if (player == "Koning")
		return std::make_shared<King>();
	else if (player == "Prediker")
		return std::make_shared<Preacher>();
	else if (player == "Koopman")
		return std::make_shared<Merchant>();
	else if (player == "Bouwmeester")
		return std::make_shared<Builder>();
	else if (player == "Condottiere")
		return std::make_shared<Condottiere>();
	else
		return nullptr;
}