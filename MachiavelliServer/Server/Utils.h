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
	static std::string ToLowerCase(std::string string);
    static std::string &ltrim(std::string &s);
    static std::string &rtrim(std::string &s);
    static std::string &trim(std::string &s);
    static std::string ToLowerAndTrim(std::string string);
    static int ParseInt(std::string stoi);
};

