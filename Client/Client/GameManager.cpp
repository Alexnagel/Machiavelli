#include "GameManager.h"


GameManager::GameManager()
{
	networkServices = new NetworkServices();
	bool success = networkServices->ConnectToServer();
    
    if (success)
    {
        // Wait for the handler threads to finish
        networkServices->WaitForThreads();
    }
    
    std::cerr << "Press 'enter' to close the program";
    std::cin.ignore();
}

GameManager::~GameManager()
{
}