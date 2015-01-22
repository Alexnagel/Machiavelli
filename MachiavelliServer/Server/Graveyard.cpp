//
//  Graveyard.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Graveyard.h"

Graveyard::Graveyard() : BuildCard("y", 2, CardColor::PURPLE, "", false, true)
{
}

Graveyard::~Graveyard()
{

}

void Graveyard::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{

}

BuildingEnum Graveyard::GetType()
{
	return BuildingEnum::GRAVEYARD;
}