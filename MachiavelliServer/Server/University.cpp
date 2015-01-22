//
//  University.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "University.h"

University::University() : BuildCard("", 2, CardColor::PURPLE, "", false, true)
{
}

University::~University()
{

}

void University::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{

}

BuildingEnum University::GetType()
{
	return BuildingEnum::UNIVERSITY;
}