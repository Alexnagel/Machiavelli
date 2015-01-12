#pragma once
//=============================================================================
// socket.h 
// (c) 8-12-2010, Frans Spijkerman, Avans Hogeschool
// enhanced for cross-platform use by Bob Polis (c) 2013, 2014
//
// Definition of classes Socket, ServerSocket and CientSocket
//
// Socket:
//	Abstraction of tcp-socket using Windows Sockets API (WSA)
//
// ServerSocket:
//  Socket to listen to clients on a tcp-port
//
// ClientSocket:
//	Socket to connect to a server on a tcp-port
//=============================================================================

#if defined(__APPLE__) || defined(__linux__)
#include <sys/socket.h>
typedef int SOCKET;
#else // Windows
#include <winsock2.h>
typedef long ssize_t;
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <memory>

#include "throw.h"

class Socket
{
protected:
	SOCKET sock;
	struct sockaddr addr;
    bool is_client_prompted;

public:
	Socket() : sock(0), is_client_prompted(false) {}
	Socket(SOCKET sock, const struct sockaddr& address) : sock(sock), addr(address) {}
	virtual ~Socket();

	SOCKET get() const { return sock; }
	void set(SOCKET sock) { this->sock = sock; }
	void close();
	std::string get_dotted_ip() const;

	ssize_t read(char *buf, size_t maxlen);
	std::string readline();

	void write(const std::string& msg);
	void write(const char *buf, size_t len);
    
    bool IsClientPrompted();
    void SetClientPrompted(bool isPrompted);
};