//
//  ServerSocket.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 10-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__ServerSocket__
#define __Machiavelli__ServerSocket__

#include "Socket.h"

class ServerSocket : public Socket
{
public:
    ServerSocket(int port);
    Socket* accept();
};

#endif /* defined(__Machiavelli__ServerSocket__) */
