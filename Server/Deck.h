#pragma once

#include <vector>
#include <algorithm>
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

	T Get(int index) const
	{
		try {
			return list.at(index);
		}
		catch (...)	{
			std::cout << "Index doesnt exist" << std::endl;
		}
	}

	// Setters
	void Add(const T& elem)
	{
		list.push_back(elem);
	}

	void Shuffle()
	{
		//shuffle(vec.begin(), vec.end(), dre);
		std::shuffle(list.begin(), list.end(), Utils::GetRandomEngine());
	}
};

