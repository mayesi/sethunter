#pragma once
#include "GameLevel.h"
#include "Spritesheet.h"
#include "PlayerCar.h"
#include "Graphics.h"
#include <vector>
#include <random>
#include <chrono>

typedef struct PlantSquare
{
	float x;	// x coordinate
	float y;	// y coordinate
	int plant;	// -1 no plant, or index of plant
} PlantSquare;


/* 
	This class has the logic for Level 1 in the game. It inherits from GameLevel.
*/
class Level1 : public GameLevel
{
	SpriteSheet* background;
	PlayerCar* playerCar;		// The player's car
	SpriteSheet* plants[3];		// Holds the three different plant sprites that can be put on the screen
	std::vector<PlantSquare> plantSquares;	// The grid that the plants are placed in


public:
	static const int WIN_WIDTH = 1024;	// the window width
	static const int WIN_HEIGHT = 768;	// the window height

	const float carStartx = 500.0;
	const float carStarty = 660.0;
	const int numSquareX = 10;
	const int numSquareY = 10;

	std::default_random_engine generator;

	void Load() override;	// Loads the sprites and sets up the initial state of the game.
	void Unload() override;	// Unloads resources
	void Update() override;	// Updates the state of game objects
	void Render() override;	// Renders the screen

	void PlacePlants();		// Randomly draw plants on the screen
	void UpdatePlants();	// Randomly places plants somewhere in the grid
	void SetupGrid();		// Sets up the plantSquares vector with coordinates etc.
	void DrawRoad();	// Draws the background
};


