//
//  Smithy.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Smithy.h"
#include "GameManager.h"
#include "NetworkServices.h"

Smithy::Smithy() : BuildCard("Smithy", 5, CardColor::PURPLE, "Once during your turn, you may pay two gold to draw 3 building cards.")
{
}

void Smithy::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
    std::shared_ptr<Socket> socket = player->GetSocket();
    std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();
    
    bool chosen = false;
    while (!chosen)
    {
        networkServices->WriteToClient("You may pay 3 gold to receive two building cards. Do you want to use this card? (yes or no)\n", socket, true);
        std::string choice = Utils::ToLowerAndTrim(networkServices->PromptClient(player));
        
        if (choice == "yes")
        {
            networkServices->WriteToClient("You have chosen to draw two building cards\n", socket);
            
            if (player->GetGold() >= 3)
            {
                player->RemoveGold(3);
                std::vector<std::shared_ptr<BuildCard>> taken_cards = manager->TakeCards(2);
                
                networkServices->WriteToClient("You have received the following cards:\n", socket);
                for (std::shared_ptr<BuildCard> buildCard : taken_cards)
                {
                    networkServices->WriteToClient("  " + buildCard->GetCardString() + "\n", socket);
                }
                
                player->AddBuildCards(taken_cards);
            }
            else
            {
                networkServices->WriteToClient("You do not have sufficient gold to draw the two cards.\n", socket);
            }
            chosen = true;
        }
        else if (choice == "no")
        {
            chosen = true;
        }
        else
            networkServices->WriteToClient("This is not a valid option.\n", socket);
    }
}

BuildingEnum Smithy::GetBuildingType()
{
    return BuildingEnum::SMITHY;
}


Smithy::~Smithy()
{
}