#pragma once
#include <random>
#include <chrono>

class Randomizer
{
private:
	std::default_random_engine generator;	// Random number generator for integers

public:
	Randomizer();
	~Randomizer();

	float RandNumber(float min, float max, int interval);
	int GetChoice(int numChoices);
};

