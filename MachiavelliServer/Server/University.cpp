//
//  University.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//


#include "University.h"

University::University() : BuildCard("University", 6, CardColor::PURPLE, "This card is worth 8 points at the end of the game", false, true)
{
    
}

void University::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
    
}

BuildingEnum University::GetBuildingType()
{
    return BuildingEnum::UNIVERSITY;
}


University::~University()
{
    
}