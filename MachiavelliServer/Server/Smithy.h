//
//  Smithy.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__Smithy__
#define __Machiavelli__Smithy__

#include "BuildCard.h"
#include <vector>

class Smithy : public BuildCard
{
public:
    Smithy();
    ~Smithy();
    
    void UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
    BuildingEnum GetBuildingType();
};


#endif /* defined(__Machiavelli__Smithy__) */
