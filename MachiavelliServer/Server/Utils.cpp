#include "Utils.h"
#include <functional>
#include <cctype>

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

std::string Utils::ToLowerCase(std::string string)
{
	for (int i = 0; i < string.length(); i++)
	{
		string[i] = tolower(string[i]);
	}
	return string;
}



// trim from start
std::string &Utils::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &Utils::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &Utils::trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::string Utils::ToLowerAndTrim(std::string string)
{
    std::string lower = ToLowerCase(string);
    return trim(lower);
}