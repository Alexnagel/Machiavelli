//
//  Socket.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 03-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__Socket__
#define __Machiavelli__Socket__

#if defined(__APPLE__) || defined(__linux__)
    #include <sys/socket.h>
    typedef int SOCKET;
#else // Windows
    #include <winsock2.h>
    typedef long ssize_t;
#endif

#include <iostream>
#include <string>

class Socket
{
protected:
    SOCKET sock;
    struct sockaddr addr;
    
public:
    Socket();
    Socket(SOCKET sock, const struct sockaddr& address);
    virtual ~Socket();
    
    SOCKET get() const;
    void set(SOCKET sock);
    void close();
    std::string get_dotted_ip() const;
    
    ssize_t read(char *buf, size_t maxlen);
    std::string readline();
    
    void write(const std::string& msg);
    void write(const char *buf, size_t len);
};

#endif /* defined(__Machiavelli__Socket__) */
