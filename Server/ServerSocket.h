//
//  ServerSocket.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 10-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__ServerSocket__
#define __Machiavelli__ServerSocket__

#if defined(__APPLE__) || defined(__linux__)

#include "Socket.h"
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

class WSA
{
private:
    WSADATA data;
public:
    WSA()
    {
        int iResult = WSAStartup(MAKEWORD(2, 2), &data);
        if (iResult != 0) {
            std::cerr << "WSAStartup failed with error: " << iResult << '\n';
        }
    }
    ~WSA()
    {
        WSACleanup();
    }
} wsa; // instance

#endif // Windows

class ServerSocket : public Socket
{
public:
    ServerSocket(int port);
    Socket* accept();
};

#endif /* defined(__Machiavelli__ServerSocket__) */
