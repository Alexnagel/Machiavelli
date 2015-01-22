//
//  HauntedCity.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "HauntedCity.h"
#include "GameManager.h"
#include "NetworkServices.h"

HauntedCity::HauntedCity() : BuildCard("Haunted City", 2, CardColor::PURPLE, "For the purposes of victory points, the Haunted City is conisdered to be of the color of your choice", false, true)
{
}

void HauntedCity::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
    std::shared_ptr<Socket> socket = player->GetSocket();
    std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();
    
    bool color_chosen = false;
    while (!color_chosen)
    {
        networkServices->WriteToClient("This card can be changed to the color of your choice. \n", socket);
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
    card_used = true;
}

BuildingEnum HauntedCity::GetBuildingType()
{
    return BuildingEnum::HAUNTEDCITY;
}


HauntedCity::~HauntedCity()
{
    
}