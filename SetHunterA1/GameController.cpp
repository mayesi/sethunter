
#include "GameController.h"

GameLevel* GameController::currentLevel;	// Global variable, the GameLevel object
bool GameController::Loading;				// Global variable, whether things are loading 

/*
	Method:			Init()
	Description:	Sets Loading to true and the currentLevel to 0
*/
void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}

/*
	Method:			LoadInitialLevel()
	Description:	Calls the Load() method for the GameLevel object to set up the level
	Parameters:
		GameLevel* lev - the 'level' for the game
*/
void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true;			// This can help us avoid loading activity while rendering
	currentLevel = lev;
	currentLevel->Load();	// Sets up the game level
	Loading = false;
}

/*
	Method:			SwitchLevel()
	Description:	Unloads and deallocates resources for the current level and loads the passed in GameLevel
	Parameters:
		GameLevel* lev - the next GameLevel to load
*/
void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel->Unload();	// Unloads GameLevel resources
	lev->Load();			// Loads the new 'level'
	delete currentLevel;	// Deallocates memory used by object currentLevel is pointing to
	currentLevel = lev;		// set currentLevel to point to the new GameLevel object in memory
	Loading = false;
}

/*
	Method:			Render()
	Description:	Renders the screen
*/
void GameController::Render()
{
	if (Loading) return;	// nice! Do not update or render if the scene is loading.
	currentLevel->Render();
}

/*
	Method:			Update()
	Description:	Updates the state of the game objects
*/
void GameController::Update()
{
	if (Loading) return;	// nice! Do not update or render if the scene is loading.
	currentLevel->Update();
}