//
//  Socket.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 03-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

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

Socket::Socket() : sock(0)
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

ssize_t Socket::read(char *buf, size_t maxlen)
{
	ssize_t len = 0;
	// might come in parts
	while (ssize_t n = ::recv(sock, buf + len, int(maxlen - len), 0)) {
		throw_if_min1((int)n);
		len += n;
		if (len >= maxlen) break;
	}
	return len;
}

std::string Socket::readline()
{
	// read a line: ignore '\r', stop at '\n'
	std::string line;
	char c;
	while (ssize_t n = ::recv(sock, &c, 1, 0)) {
		throw_if_min1((int)n);
		if (c == '\n') break;
		if (c != '\r') line += c;
	}
	return line;
}

void Socket::write(const std::string& msg)
{
	write(msg.c_str(), msg.length());
}

void Socket::write(const char *buf, size_t len)
{
	throw_if_min1((int)::send(sock, buf, (int)len, 0));
}

std::string Socket::get_dotted_ip() const
{
	if (addr.sa_family == AF_INET || addr.sa_family == AF_INET6) {
		char textbuf[INET6_ADDRSTRLEN]; // large enough for both IPv4 and IPv6 addresses

		return ::inet_ntop(addr.sa_family, (void*)&addr, textbuf, INET6_ADDRSTRLEN);
	}
	return "n/a";
}

void Socket::close()
{
#if defined(__APPLE__) || defined(__linux__)
	throw_if_min1(::close(sock));
#else
	::closesocket(sock);
#endif

	sock = 0;
}

Socket::~Socket()
{
	if (sock > 0) close();
}