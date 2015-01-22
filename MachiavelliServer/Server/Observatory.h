//
//  Observatory.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__Observatory__
#define __Machiavelli__Observatory__

#include "BuildCard.h"

class Observatory : public BuildCard
{
public:
    Observatory();
    ~Observatory();
    
    void UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
    BuildingEnum GetBuildingType();
};

#endif /* defined(__Machiavelli__Observatory__) */
