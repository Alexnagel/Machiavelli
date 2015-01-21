//
//  Keep.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__Keep__
#define __Machiavelli__Keep__

#include "BuildCard.h"
#include <vector>

class Keep : public BuildCard
{
public:
    Keep();
    ~Keep();
    
    void UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player);
};


#endif /* defined(__Machiavelli__Keep__) */
