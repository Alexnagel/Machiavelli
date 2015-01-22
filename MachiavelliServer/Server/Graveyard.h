//
//  Graveyard.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__Graveyard__
#define __Machiavelli__Graveyard__

#include "BuildCard.h"
#include <vector>

class GraveYard : public BuildCard
{
public:
    GraveYard();
    ~GraveYard();
    
    void UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
    BuildingEnum GetBuildingType();
};

#endif /* defined(__Machiavelli__Graveyard__) */
