#pragma once

#include <iostream>

class Card
{
public:
	Card(std::string name);
	virtual ~Card();
	virtual std::string GetName() = 0;

protected:
	std::string name;
};