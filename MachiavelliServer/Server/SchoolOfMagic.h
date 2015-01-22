//
//  SchoolOfMagic.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__SchoolOfMagic__
#define __Machiavelli__SchoolOfMagic__

#include "BuildCard.h"
#include <vector>

class SchoolOfMagic : public BuildCard
{
public:
    SchoolOfMagic();
    ~SchoolOfMagic();
    
    void UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
    BuildingEnum GetBuildingType();
};

#endif /* defined(__Machiavelli__SchoolOfMagic__) */
