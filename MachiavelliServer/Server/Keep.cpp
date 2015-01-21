//
//  Keep.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 21-01-15.
//  Copyright (c) 2015 Alex Nagelkerke. All rights reserved.
//

#include "Keep.h"
#include "GameManager.h"
#include "NetworkServices.h"

Keep::Keep() : BuildCard("Keep", 3, CardColor::PURPLE, "Once during your turn, you may discard a building card from your hand and receive one gold from the bank", true, false)
{
}

void Keep::UseCardSpecial(std::shared_ptr<GameManager> manager, std::shared_ptr<Player> player)
{
    std::shared_ptr<Socket> socket = player->GetSocket();
    std::shared_ptr<NetworkServices> networkServices = manager->GetNetworkServices();
    
    networkServices->WriteToClient("You may discard one of your building cards and receive one gold from the bank", socket);
    
    std::vector<std::shared_ptr<BuildCard>> cards = player->GetAllBuildCards();
    
    bool card_discarded = false;
    while (!card_discarded)
    {
        std::string hand_cards = "Available cards:\n";
        
        for (int i = 0; i < cards.size(); i++)
        {
            hand_cards.append("   [" + std::to_string(i) + "] " + cards[i]->GetCardString() + "\n");
        }
        networkServices->WriteToClient("Choose one of the above cards", socket, true);
        std::string number = Utils::ToLowerAndTrim(networkServices->PromptClient(player));
        
        int iNumber = -1;
        try
        {
            iNumber = std::stoi(number);
        }
        catch (std::invalid_argument &e)
        {
            // invalid parse
            networkServices->WriteToClient("This is not a valid option\n", socket);
            continue;
        }
        catch (std::out_of_range &e)
        {
            // overflow
            networkServices->WriteToClient("This is not a valid option\n", socket);
            continue;
        }
        
        if (iNumber > -1 && iNumber < cards.size())
        {
            std::shared_ptr<BuildCard> card = cards[iNumber];
            player->RemoveBuildCard(iNumber);
            player->AddGold(1);
            
            networkServices->WriteToClient("You have removed '" + card->GetName() + "' from your hand and received one gold in return\n", socket);
            card_discarded = true;
        }
    }
}

Keep::~Keep()
{
    
}