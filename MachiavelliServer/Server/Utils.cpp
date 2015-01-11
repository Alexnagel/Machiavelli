#include "Utils.h"

int Utils::seed = std::random_device()();
std::mt19937 Utils::rng = std::mt19937(Utils::seed);

int Utils::RandomNumber(int max)
{
	return std::uniform_int_distribution<int>(0, max)(rng);
}

int Utils::RandomNumber(int min, int max)
{
	return std::uniform_int_distribution<int>(min, max)(rng);
}

std::default_random_engine Utils::GetRandomEngine()
{
	std::random_device dev;
	std::default_random_engine dre(dev());
	return dre;
}