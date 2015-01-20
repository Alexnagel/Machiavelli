//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "GameManager.h"

int main(int argc, const char * argv[])
{
	// Create the manager
	std::shared_ptr<GameManager> manager = std::make_shared<GameManager>();
	manager->RunServer();

	return 0;
}