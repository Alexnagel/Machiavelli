#include "GameManager.h"


GameManager::GameManager()
{
	//ClientSocket("127.0.0.1", 1080);
	networkServices = new NetworkServices();
	networkServices->ConnectToServer();

	while (networkServices->IsConnected()) {

	}
}

GameManager::~GameManager()
{
}