//
//  HauntedCity.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__HauntedCity__
#define __Machiavelli__HauntedCity__

#include "BuildCard.h"
#include "BuildingEnum.h"

class HauntedCity : public BuildCard
{
public:
    HauntedCity();
    virtual ~HauntedCity();
    
    void UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
	BuildingEnum GetType();
};

#endif /* defined(__Machiavelli__HauntedCity__) */
