#pragma once

#include <iostream>
#include <vector>

#include "Player.h"

class GameManager
{
private:
	std::vector<Player> players;

public:
	GameManager();
	~GameManager();

	Player GetPlayer(int i);

};

