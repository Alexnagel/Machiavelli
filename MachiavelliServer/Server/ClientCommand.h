//
//  ClientCommand.h
//  socketexample
//
//  Created by Bob Polis on 27/11/14.
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef __socketexample__ClientCommand__
#define __socketexample__ClientCommand__

#include <string>
#include <memory>
#include "Socket.h"

class ClientCommand {
public:
	ClientCommand() {}
	ClientCommand(const std::string& cmd, std::shared_ptr<Socket> client) : cmd(cmd), client(client), promptUser(false) {}
    ClientCommand(const std::string& cmd, std::shared_ptr<Socket> client, bool prompt) : cmd(cmd), client(client), promptUser(prompt) {}

    std::string get_cmd() const { return promptUser ? cmd + "\n> " : cmd; }
    void set_cmd(const std::string& command) { cmd = command; }

	std::shared_ptr<Socket> get_client() const { return client; }
	void set_client(std::shared_ptr<Socket> socket) { client = socket; }

private:
	std::string cmd;
	std::shared_ptr<Socket> client;
    bool promptUser;
};

#endif /* defined(__socketexample__ClientCommand__) */
