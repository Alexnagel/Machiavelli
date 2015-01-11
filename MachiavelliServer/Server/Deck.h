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
        return T();
	}

	T TakeCard(int index)
	{
		try {
			T temp = list.at(index);
			list.erase(list.begin() + index);
			return temp;
		}
		catch (...) {
			std::cout << "Index doesnt exist" << std::endl;
		}
	}

	T Peek()
	{
		return list.at(list.size() - 1);
	}

	T Pop()
	{
		T temp = list.at(list.size() - 1);
		list.erase(list.size() - 1);
		return temp;
	}

	// Setters
	void Add(const T& elem)
	{
		list.push_back(elem);
	}

	void Remove(int i)
	{
		if (list.size() > i)
		{
			list.erase(list.begin() + i);
		}
	}

	void RemoveLast()
	{
		if (list.size() > 0)
		{
			list.erase(list.end() - 1);
		}
	}

	void Shuffle()
	{
		//shuffle(vec.begin(), vec.end(), dre);
		std::shuffle(list.begin(), list.end(), Utils::GetRandomEngine());
	}
};