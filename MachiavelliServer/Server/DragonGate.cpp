//
//  DragonGate.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "DragonGate.h"

DragonGate::DragonGate() : BuildCard("Dragon Gate", 6, CardColor::PURPLE, "This card is worth 8 points at the end of the game")
{
    
}

void DragonGate::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
    
}

BuildingEnum DragonGate::GetBuildingType()
{
    return BuildingEnum::DRAGONGATE;
}


DragonGate::~DragonGate()
{
}