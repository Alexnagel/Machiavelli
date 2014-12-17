//
//  ConnectionException.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 10-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#ifndef __Machiavelli__ConnectionException__
#define __Machiavelli__ConnectionException__

#include <exception>
#include <string>

class ConnectionException : public std::exception
{
private:
    std::string message;
    
public:
    const char* what() const throw();
    ConnectionException(std::string m);
    ~ConnectionException();
};

#endif /* defined(__Machiavelli__ConnectionException__) */
