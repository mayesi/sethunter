#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"
#include "KeyboardInput.h"

/*
	This abstract class defines the methods that can be used for Level classes for the game.
*/
class GameLevel
{
protected:
	static Graphics* gfx;
	static KeyboardInput* keyboard;

public:
	static const int WIN_WIDTH = 1024;	// the window width
	static const int WIN_HEIGHT = 768;	// the window height

	/* Sets this class's Graphics object to the passed in Graphics object */
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	static void Init(Graphics* graphics, KeyboardInput* input)
	{
		gfx = graphics;
		keyboard = input;
	}

	virtual void Load() = 0;	// Loads the sprites and sets up the initial state of the game.
	virtual void Unload() = 0;	// Unloads resources
	virtual void Update() = 0;	// Updates the state of game objects
	virtual void Render() = 0;	// Renders the screen 
};