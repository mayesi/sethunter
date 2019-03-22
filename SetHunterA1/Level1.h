#pragma once
#include "GameLevel.h"
#include "Spritesheet.h"
#include "PlayerCar.h"
#include "Graphics.h"
#include <vector>
#include <random>
#include <chrono>
#include <queue>
#include <cstdlib>

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
	// The leftmost and rightmost x positon allowed for the left side of the road
	const float ROAD_LEFT_X_LEFTMOST = GameLevel::WIN_WIDTH / 10;
	const float ROAD_LEFT_X_RIGHTMOST = GameLevel::WIN_WIDTH / 10 * 6;
	const float ROAD_STARTING_X = GameLevel::WIN_WIDTH / 10 * 3;	// the road's starting point
	const float MIN_BEND = 1.0f;	// The minimum bend, in pixels per line
	const float MAX_BEND = 10.0f;	// The maximum bend, in pixels per line
	const int BEND_INTERVAL = 10;	// The number of possible curve values
	const float MIN_STRAIGHT = GameLevel::WIN_HEIGHT / 3;	// The minimum length of a straight section of road
	const float MAX_STRAIGHT = GameLevel::WIN_HEIGHT;		// The maximum length of a straight section of road
	const float ROAD_WIDTH = GameLevel::WIN_WIDTH / 10 * 3;	// default road width in pixels

	PlayerCar* playerCar;		// The player's car
	SpriteSheet* plants[3];		// Holds the three different plant sprites that can be put on the screen
	std::vector<PlantSquare> plantSquares;	// The grid that the plants are placed in
	std::default_random_engine generator;	// Random number generator for integers
	float targetLeftx;	// Where the left pixel of the road is meant to go, used for drawing
	float bendValue;	// How much to curve the road, <0 curve left, 0 straight, >0 curve right
	float straightLength;		// The length of a straight section of road
	std::deque<float> roadDims;	// The road dimensions

	int GetChoice(int numChoices);	// Pick one of numChoices choices
	void InitRoad();	// Initializes the road dimensions with x-values, one x-value for each y value
	void ShiftRoad(int direction);	// Shifts the road dimensions for movement 'down' the screen
	void SetNewCurve();	// Sets up the next curve in the road
	float RandNumber(float min, float max, int interval);	// Random number, float

public:
	static const int WIN_WIDTH = 1024;	// the window width
	static const int WIN_HEIGHT = 768;	// the window height

	const float CAR_START_X = WIN_WIDTH*0.45;	// start in the middle of the screen
	const float CAR_START_Y = WIN_HEIGHT*0.8;	// start a bit from the bottom of the screen
	const int NUM_SQUARE_X = 10;	// 'divide' the screen into this number of squares
	const int NUM_SQUARE_Y = 10;	// 'divide' the screen into this number of squares

	void Load() override;	// Loads the sprites and sets up the initial state of the game.
	void Unload() override;	// Unloads resources
	void Update() override;	// Updates the state of game objects
	void Render() override;	// Renders the screen

	void PlacePlants();		// Randomly draw plants on the screen
	void UpdatePlants();	// Randomly places plants somewhere in the grid
	void SetupGrid();		// Sets up the plantSquares vector with coordinates etc.
	void DrawRoad();		// Draws the background

};


