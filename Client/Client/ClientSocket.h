//
//  ClientSocket.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 03-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__ClientSocket__
#define __Machiavelli__ClientSocket__

#include "Socket.h"
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <memory>

#include "ConnectionException.h"

class ClientSocket : public Socket
{
public:
	ClientSocket(const char *host, int port);
};

#endif /* defined(__Machiavelli__ClientSocket__) */
