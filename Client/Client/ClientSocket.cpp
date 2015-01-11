//
//  ClientSocket.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 03-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#include "ClientSocket.h"

#include "Socket.h"
#include "throw.h"

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

#else // Windows

#include <ws2tcpip.h>

// Tell linker to use these libraries
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

//class WSA
//{
//private:
//	WSADATA data;
//public:
//	WSA()
//	{
//		int iResult = WSAStartup(MAKEWORD(2, 2), &data);
//		if (iResult != 0) {
//			std::cerr << "WSAStartup failed with error: " << iResult << '\n';
//		}
//	}
//	~WSA()
//	{
//		WSACleanup();
//	}
//} wsa; // instance

#endif // Windows

ClientSocket::ClientSocket(const char *host, int port)
{
	// construct network address for server
	struct addrinfo hint;
	std::memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;

	struct addrinfo* infolist{ nullptr };
	int gai_error = ::getaddrinfo(host, std::to_string(port).c_str(), &hint, &infolist);

	if (gai_error)
	{
		std::ostringstream oss;
		oss << "getaddrinfo error " << gai_error << ": " << gai_strerror(gai_error) << " (" << __FILE__ << ":" << __LINE__ << ")";
		throw ConnectionException(oss.str());
	}

	// wrap our list pointer inside unique_ptr for auto cleanup
#if defined(__APPLE__) || defined(__linux__)
	using cleanup_func = void(*)(struct addrinfo*);
	std::unique_ptr<struct addrinfo, cleanup_func> list{ infolist, ::freeaddrinfo };
#else // Windows
	using cleanup_func = void(__stdcall*)(PADDRINFOA);
	std::unique_ptr<struct addrinfo, cleanup_func> list(infolist, ::freeaddrinfo);
#endif

	// create socket
	throw_if_min1(sock = ::socket(list->ai_family, list->ai_socktype, list->ai_protocol));

	// connect to server
	throw_if_min1(::connect(sock, (struct sockaddr*)list->ai_addr, list->ai_addrlen));
}


