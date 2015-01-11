//#include "ClientSocket.h"
#include "NetworkServices.h"

#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	NetworkServices* networkServices;
};

