//
//  ServerCommand.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 17-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#ifndef Machiavelli_ServerCommand_h
#define Machiavelli_ServerCommand_h

#include <string>
#include <memory>
#include "Socket.h"

class ServerCommand {
public:
	ServerCommand() {}
	ServerCommand(const std::string& cmd, std::shared_ptr<Socket> p_server) : cmd(cmd), server(p_server) {}

	std::string get_cmd() const { return cmd; }
	void set_cmd(const std::string& command) { cmd = command; }

	std::shared_ptr<Socket> get_server() const { return server; }
	void set_server(std::shared_ptr<Socket> socket) { server = socket; }

private:
	std::string cmd;
	std::shared_ptr<Socket> server;
};

#endif
