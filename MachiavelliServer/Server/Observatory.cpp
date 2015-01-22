//
//  Observatory.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Observatory.h"

Observatory::Observatory() : BuildCard("", 2, CardColor::PURPLE, "", false, true)
{
}

Observatory::~Observatory()
{

}

void Observatory::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{

}

BuildingEnum Observatory::GetType()
{
	return BuildingEnum::OBSERVATORY;
}