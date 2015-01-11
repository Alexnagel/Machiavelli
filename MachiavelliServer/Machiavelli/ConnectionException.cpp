//
//  ConnectionException.cpp
//  Machiavelli
//
//  Created by Alex Nagelkerke on 10-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#include "ConnectionException.h"

ConnectionException::ConnectionException(std::string m) : message(m)
{}

ConnectionException::~ConnectionException()
{}

const char* ConnectionException::what() const throw()
{
    return message.c_str();
}