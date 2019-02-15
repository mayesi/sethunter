#pragma once

#include "GameLevel.h"
#include "Graphics.h"

//This will be a Singleton class (constructor is private)

class GameController
{
	GameController() {}				// Constructor
	static GameLevel* currentLevel;	// GameLevel object
public:
	static bool Loading;	// Indicates whether assets are being loaded
	static void Init();		// 
	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);
	static void Render();
	static void Update();
};