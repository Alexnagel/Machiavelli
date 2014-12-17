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

#if defined(__APPLE__) || defined(__linux__)

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/route.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <netinet/ip.h>

#else // Windows

#include <ws2tcpip.h>

// Tell linker to use these libraries
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#endif // Windows

class ServerSocket : public Socket
{
public:
    ServerSocket(int port);
    Socket* accept();
};

#endif /* defined(__Machiavelli__ServerSocket__) */
