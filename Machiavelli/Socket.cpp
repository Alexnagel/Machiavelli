//
//  Socket.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 03-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#include "Socket.h"

Socket::Socket(): sock(0)
{
}

Socket::Socket(SOCKET sock, const struct sockaddr& address) : sock(sock), addr(address)
{
}

SOCKET Socket::get() const
{
    return sock;
}

void Socket::set(SOCKET sock)
{
    this->sock = sock;
}