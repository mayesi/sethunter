#pragma once
#include <Windows.h>


//https://www.braynzarsoft.net/viewtutorial/q16390-15-high-resolution-timer
class GameTimer
{
	double countsPerSecond = 0.0;
	__int64 CounterStart = 0;

	int frameCount = 0;
	int fps = 0;

	__int64 frameTimeOld = 0;
	double frameTime;

public:
	GameTimer();	// Constructor
	~GameTimer();	// Destructor
	void StartTimer();
	double GetTime();
	double GetFrameTime();
};