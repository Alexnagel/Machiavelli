//
//  Library.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Library.h"

Library::Library() : BuildCard("", 2, CardColor::PURPLE, "", false, true)
{
}

Library::~Library()
{

}

void Library::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{

}

BuildingEnum Library::GetType()
{
	return BuildingEnum::LIBRARY;
}