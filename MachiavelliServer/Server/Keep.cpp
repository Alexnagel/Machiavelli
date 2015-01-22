//
//  Keep.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Keep.h"
#include "GameManager.h"
#include "NetworkServices.h"

Keep::Keep() : BuildCard("Keep", 3, CardColor::PURPLE, "The Keep cannot be destroyed by the Condottiere")
{
}

void Keep::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
}

BuildingEnum Keep::GetBuildingType()
{
    return BuildingEnum::KEEP;
}

Keep::~Keep()
{
    
}