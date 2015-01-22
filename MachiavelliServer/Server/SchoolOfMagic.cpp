//
//  SchoolOfMagic.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "SchoolOfMagic.h"

SchoolOfMagic::SchoolOfMagic() : BuildCard("", 2, CardColor::PURPLE, "", false, true)
{
}

SchoolOfMagic::~SchoolOfMagic()
{

}

void SchoolOfMagic::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{

}

BuildingEnum SchoolOfMagic::GetType()
{
	return BuildingEnum::MAGICSCHOOL;
}