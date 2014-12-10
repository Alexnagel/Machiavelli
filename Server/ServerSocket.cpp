//
//  ServerSocket.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 10-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#include "ServerSocket.h"

ServerSocket::ServerSocket(int port)
{
    throw_if_min1(sock = ::socket(AF_INET, SOCK_STREAM, 0));
    
    struct sockaddr_in saServer;
    saServer.sin_family = AF_INET;
    saServer.sin_addr.s_addr = INADDR_ANY;
    saServer.sin_port = htons(port);
    
    throw_if_min1(::bind(sock, (struct sockaddr*)&saServer, sizeof(struct sockaddr)));
    throw_if_min1(::listen(sock, 100));  // the number of clients that can be queued
}

Socket *ServerSocket::accept()
{
    struct sockaddr client_addr;
    client_addr.sa_family = AF_INET;
    socklen_t len = sizeof(client_addr);
    int fd;
    throw_if_min1(fd = ::accept(sock, &client_addr, &len));
    Socket* client = new Socket(fd, client_addr);
    std::cerr << "Connection accepted from "
    << client->get_dotted_ip() << ", with socket "
    << fd << std::endl;
    return client;
}