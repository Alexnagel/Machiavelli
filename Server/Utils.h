#pragma once

#include <random>

class Utils
{
private:
	static int seed;
	static std::mt19937 rng;

public:
	static int RandomNumber(int max);
	static int RandomNumber(int min, int max);
};

