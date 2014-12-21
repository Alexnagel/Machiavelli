#pragma once

#include <vector>
#include "Utils.h"

template<typename T>
class Deck
{
private:
	std::vector<T> list;

public:
	Deck(){}
	~Deck(){}

	// Operators
	Deck<T>& operator=(const Deck& other)
	{
		if (this != &other)
		{
			list = other.list;
		}
		return *this;
	}

	// Getters
	int Size() const
	{
		return list.size();
	}

	T Get(int) const
	{
		if (index < list.size())
			return list.at(index);
		else
			return;
	}

	// Setters
	void Add(const T& elem)
	{
		list.push_back(elem);
	}

	void Shuffle()
	{
		std::shuffle(list.begin(), list.end(), Utils::RandomNumber(list.size() - 1))
	}
};

