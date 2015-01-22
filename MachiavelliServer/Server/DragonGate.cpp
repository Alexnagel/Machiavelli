//
//  DragonGate.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "DragonGate.h"

DragonGate::DragonGate() : BuildCard("", 2, CardColor::PURPLE, "", false, true)
{
}

DragonGate::~DragonGate()
{

}

void DragonGate::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{

}

BuildingEnum DragonGate::GetType()
{
	return BuildingEnum::DRAGONGATE;
}