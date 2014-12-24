#pragma once

#include <random>
#include <algorithm>

class Utils
{
private:
	static int seed;
	static std::mt19937 rng;
	static std::random_device dev;
	static std::default_random_engine dre;

public:
	static int RandomNumber(int max);
	static int RandomNumber(int min, int max);

	static std::default_random_engine GetRandomEngine();
};

