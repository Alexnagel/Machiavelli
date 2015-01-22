//
//  Smithy.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Smithy.h"

Smithy::Smithy() : BuildCard("", 2, CardColor::PURPLE, "", false, true)
{
}

Smithy::~Smithy()
{

}

void Smithy::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{

}

BuildingEnum Smithy::GetType()
{
	return BuildingEnum::SMITHY;
}