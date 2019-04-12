#include "Randomizer.h"



Randomizer::Randomizer()
{
	// Seed the two random number generators, one is optimized for integers, one is for floats
	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	generator.seed(seed);
	srand(time(NULL)); // Also seed srand...
}


Randomizer::~Randomizer()
{
}

/*
Method:		RandNumber(float min, float max, int interval)
*/
float Randomizer::RandNumber(float min, float max, int interval)
{
	float result = min + ((rand() % interval) * (max - min)) / interval;
	return result;
}


/*
	Method:		GetChoice()
	Description:
		Uses a random number generator to choose one of a passed in number of choices.
	Parameters:
		int numChoices - the number of possibilities to choose from
	Return:
		int - the choice, 0 to numChoices - 1;
*/
int Randomizer::GetChoice(int numChoices)
{
	std::uniform_int_distribution<int> whichChoice(0, numChoices - 1);	// pick 1 of numChoice choices
	return whichChoice(generator);
}

