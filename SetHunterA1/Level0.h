#pragma once
#include "GameLevel.h"

class Level0 : public GameLevel
{
public:
	void Load() override;	// Loads the sprites and sets up the initial state of the game.
	void Unload() override;	// Unloads resources
	void Update() override;	// Updates the state of game objects
	void Render() override;	// Renders the screen
};