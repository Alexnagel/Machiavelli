//
//  SchoolOfMagic.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "SchoolOfMagic.h"
#include "GameManager.h"
#include "NetworkServices.h"

SchoolOfMagic::SchoolOfMagic() : BuildCard("School of Magic", 6, CardColor::PURPLE, "During the payout fase this card will be the color of your choice. If you are King, Condottiere, Preacher or Merchant you will receive one gold")
{
    
}

void SchoolOfMagic::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
    color = CardColor::PURPLE;
    
    std::shared_ptr<Socket> socket = player->GetSocket();
    std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();
    
    if (player->GetCurrentPlayerCard()->GetType() == PlayerCardType::KING ||
        player->GetCurrentPlayerCard()->GetType() == PlayerCardType::CONDOTTIERE ||
        player->GetCurrentPlayerCard()->GetType() == PlayerCardType::PREACHER ||
        player->GetCurrentPlayerCard()->GetType() == PlayerCardType::MERCHANT)
        player->AddGold(1);
    
    bool color_chosen = false;
    while (!color_chosen)
    {
        networkServices->WriteToClient("This card can be changed to the color of your choice for this fase. \n", socket);
        networkServices->WriteToClient("Please enter a color", socket, true);
        std::string chosen_color = Utils::ToLowerAndTrim(networkServices->PromptClient(player));
        
        if (chosen_color == "yellow")
        {
            BuildCard::color = CardColor::YELLOW;
            color_chosen = true;
        }
        else if (chosen_color == "purple")
        {
            BuildCard::color = CardColor::PURPLE;
            color_chosen = true;
        }
        else if (chosen_color == "blue")
        {
            BuildCard::color = CardColor::BLUE;
            color_chosen = true;
        }
        else if (chosen_color == "red")
        {
            BuildCard::color = CardColor::RED;
            color_chosen = true;
        }
        else if (chosen_color == "green")
        {
            BuildCard::color = CardColor::GREEN;
            color_chosen = true;
        }
        else
            networkServices->WriteToClient("This is not a valid option\n", socket);
    }
}

BuildingEnum SchoolOfMagic::GetBuildingType()
{
    return BuildingEnum::MAGICSCHOOL;
}


SchoolOfMagic::~SchoolOfMagic()
{
}