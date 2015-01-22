//
//  Observatory.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Observatory.h"

#include "GameManager.h"
#include "NetworkServices.h"

Observatory::Observatory() : BuildCard("Observatory", 5, CardColor::PURPLE, "If you choose to draw cards when you take an action, you draw 3 cards, keep one of your choice, and put the other 2 on the bottom of the deck")
{
}

void Observatory::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
    
}

BuildingEnum Observatory::GetBuildingType()
{
    return BuildingEnum::OBSERVATORY;
}


Observatory::~Observatory()
{
}