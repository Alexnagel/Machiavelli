//
//  Graveyard.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Graveyard.h"
#include "GameManager.h"
#include "NetworkServices.h"

GraveYard::GraveYard() : BuildCard("Graveyard", 5, CardColor::PURPLE, "When the Condottiere destroys a building, you may pay one gold to take the destroyed building into your hand.  You may not do this if you are the Warlord", false, false)
{
    
}

void GraveYard::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
    std::shared_ptr<Socket> socket = player->GetSocket();
    std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();
    
    if (player->GetCurrentPlayerCard()->GetType() != PlayerCardType::CONDOTTIERE)
    {
        bool has_answer = false;
        while(!has_answer)
        {
            networkServices->WriteToClient("The condottiere has destroyed a building. Do you want to buy it for one gold? (yes or no)\n", socket, true);
            std::string answer = Utils::ToLowerAndTrim(networkServices->PromptClient(player));
            
            if (answer == "yes")
            {
                networkServices->WriteToClient("You have chosen to buy the destroyed building. One gold will be taken from your account.", socket);
                
                // Get building
                
                has_answer = true;
            }
            else if (answer == "no")
            {
                networkServices->WriteToClient("You have chosen not to buy the destroyed building.\n", socket);
                has_answer = true;
            }
            else
                networkServices->WriteToClient("This is not a valid option \n", socket);
        }
    }
}

BuildingEnum GraveYard::GetBuildingType()
{
    return BuildingEnum::GRAVEYARD;
}

GraveYard::~GraveYard()
{
    
}