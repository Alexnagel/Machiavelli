//
//  Library.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Library.h"

Library::Library() : BuildCard("Library", 6, CardColor::PURPLE, "If you choose to draw cards you you take an action, you keep both of the cards you have drawn.")
{
    
}

void Library::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
    
}

BuildingEnum Library::GetBuildingType()
{
    return BuildingEnum::LIBRARY;
}


Library::~Library()
{
}