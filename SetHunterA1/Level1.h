#pragma once
#include "GameLevel.h"
#include "Spritesheet.h"
#include "PlayerCar.h"
#include "Graphics.h"
#include "GameTimer.h"
#include "SoundEvent.h"
#include "AudioComponent.h"
#include "CollisionDetector.h"
#include "EnemyCar.h"
#include "Randomizer.h"
#include <vector>
//#include <random>
//#include <chrono>
#include <queue>
#include <cstdlib>


typedef struct PlantSquare
{
	float x;	// x coordinate
	float y;	// y coordinate
	int plant;	// -1 no plant, or index of plant
	bool render;
} PlantSquare;

typedef struct PlantInfo
{
	float hitOffsetx;
	float hitOffsety;
	float hitWidth;
	float hitHeight;
} PlantInfo;


/* 
	This class has the logic for Level 1 in the game. It inherits from GameLevel.
*/
class Level1 : public GameLevel
{
	// The leftmost and rightmost x positon allowed for the left side of the road
	const float ROAD_LEFT_X_LEFTMOST = GameLevel::WIN_WIDTH / 10;
	const float ROAD_LEFT_X_RIGHTMOST = GameLevel::WIN_WIDTH / 10 * 6;
	const float ROAD_STARTING_X = GameLevel::WIN_WIDTH / 10 * 3;	// the road's starting point
	const float MIN_X_OFFSET = GameLevel::WIN_WIDTH / 20; // The minimum distance between one curve and another
	const float MIN_BEND = 1.0f;	// The minimum bend, in pixels per line
	const float MAX_BEND = 3.0f;	// The maximum bend, in pixels per line
	const int BEND_INTERVAL = 10;	// The number of possible curve values
	const float MIN_STRAIGHT = GameLevel::WIN_HEIGHT / 5;	// The minimum length of a straight section of road
	const float MAX_STRAIGHT = GameLevel::WIN_HEIGHT / 2;		// The maximum length of a straight section of road
	const float STRAIGHT_INTERVAL = 10;	// The number of possible straight length values
	const float ROAD_WIDTH = GameLevel::WIN_WIDTH / 10 * 4;	// default road width in pixels
	const float CAR_START_X = WIN_WIDTH * 0.45;	// start in the middle of the screen
	const float CAR_START_Y = WIN_HEIGHT * 0.8;	// start a bit from the bottom of the screen
	const int NUM_SQUARE_X = 10;	// 'divide' the screen into this number of squares
	const int NUM_SQUARE_Y = 11;	// 'divide' the screen into this number of squares
	const int NUM_VISIBLE_SQUARE_Y = 10;	// 'divide' the screen into this number of visible squares
	const int STARTING_LIVES = 3;	// Default starting lives
	
	SpriteSheet* plants[3];		// Holds the three different plant sprites that can be put on the screen
	std::vector<PlantSquare> plantSquares;	// The grid that the plants are placed in
	std::vector<PlantInfo> plantInfo = { { 0, 0, 100, 100 }, { 20, 0, 60, 100 }, { 10, 5, 30, 40} };
	float plantOffset;			// the offset for drawing plants on the screen

	PlayerCar* playerCar;	// The player's car
	int score;				// The player's current score
	int lives;				// The player's current lives
	int difficulty = 0;		// the difficulty level
	int sceneSpeed;			// this determines the speed of the scene 'movement'	
	bool inCollision;		// used to determine if a life should be lost

	bool initialized = false;	// To see if the timer has been started for the first time
	GameTimer* timer;			// For timing the game
	
	Randomizer* randomizer;		// Used for getting random numbers
	
	float targetLeftx;	// Where the left pixel of the road is meant to go, used for drawing
	float bendValue;	// How much to curve the road, <0 curve left, 0 straight, >0 curve right
	float straightLength;		// The length of a straight section of road
	std::deque<float> roadDims;	// The road dimensions

	// The audio components to the level
	AudioComponent* audioComponent;
	SoundEvent* levelMusic;
	SoundEvent* dangerMusic;
	SoundEvent* explosionSFX;
	const std::wstring musicFile = L"action52.mp3";
	const std::wstring dangerMusicFile = L"Insane-Gameplay_Looping.mp3";
	const std::wstring explosionSFXFile = L"Explosion1.mp3";

	// The private methods
	void InitRoad();	// Initializes the road dimensions with x-values, one x-value for each y value
	void ShiftRoad();	// Shifts the road dimensions for movement 'down' the screen
	void SetNewCurve();	// Sets up the next curve in the road
	void DrawScore();	// Draws the score in the middle of the screen
	void DrawLives();	// Draws the lives in the upper left corner of the screen
	void DrawLivesScore();	// Draw the lives and score in the upper left corner of the screen
	void RenderPlants();	// Randomly draw plants on the screen
	void InitPlants();		// Sets up the plant placements at the start of the level
	void UpdatePlants();	// Randomly places plants somewhere in the grid
	void SetupGrid();		// Sets up the plantSquares vector with coordinates etc.
	bool IsRoadHere(float gridx, float gridy);	// Checks if the road is at the coordinates
	bool CheckPlayerCollision();	// Checks to see if the player sprite has collided with any objects
	void DrawRoad();		// Draws the background

public:
	static const int WIN_WIDTH = 1024;	// the window width
	static const int WIN_HEIGHT = 768;	// the window height

	void Load() override;	// Loads the sprites and sets up the initial state of the game.
	void Unload() override;	// Unloads resources
	void Update() override;	// Updates the state of game objects
	void Render() override;	// Renders the screen

};


