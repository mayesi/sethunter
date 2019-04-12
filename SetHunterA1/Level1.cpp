#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"
#include <stdio.h>


/*
	Method:			Load()
	Description:	Loads the sprites and sets up the initial state of the game.
*/
void Level1::Load()
{
	// Set up the level
	switchLevel = false;
	nextLevel = 0;

	//This is where we can specify our file system objects!
	//background = new SpriteSheet((wchar_t*)L"background.bmp", gfx);
	playerCar = new PlayerCar(CAR_START_X, CAR_START_Y, gfx);	// may want to adjust this to make it more centered
	D2D1_SIZE_F size = gfx->GetRenderTarget()->GetSize();
	Boundary playerBounds = { NULL, NULL, NULL, NULL };
	playerBounds.upper = size.height / 2;
	playerCar->SetBoundary(playerBounds);
	plants[0] = new SpriteSheet((wchar_t*)L"tree1.bmp", gfx);
	plants[0]->AddChromakey();
	plants[1] = new SpriteSheet((wchar_t*)L"tree2.bmp", gfx);
	plants[1]->AddChromakey();
	plants[2] = new SpriteSheet((wchar_t*)L"shrub1.bmp", gfx);
	plants[2]->AddChromakey();

	// construct a trivial random generator engine from a time-based seed:
	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	generator.seed(seed);
	srand(time(NULL)); // Also seed srand...
	
	// Set up the background scene
	SetupGrid();
	//UpdatePlants();
	InitRoad();
	InitPlants();
	sceneSpeed = 4.0f;
	plantOffset = 0;

	// Set up player score and lives, set up timer
	score = 0;
	lives = STARTING_LIVES;
	timer = new GameTimer();
	timer->StartTimer();

	// Load the music
	audioComponent = new AudioComponent();
	levelMusic = new SoundEvent();
	dangerMusic = new SoundEvent();

	bool result = audioComponent->LoadFile(musicFile, *levelMusic);
	if (result)
	{
		levelMusic->SetLoopForever();
		audioComponent->PlaySoundEvent(*levelMusic);
	}

	result = audioComponent->LoadFile(dangerMusicFile, *dangerMusic);
	if (result)
	{
		dangerMusic->SetLoopForever();
	}
}


/* 
	Method:			Unload()	
	Description:	This method unloads resources 
*/
void Level1::Unload()
{
	//delete background;
	delete playerCar;
	for (int i = 0; i < 3; i++) {
		delete plants[0];
	}
	audioComponent->StopSoundEvent(*levelMusic);
}


/* 
	Method:			Update()
	Description:	This method updates the state of game objects 
*/
void Level1::Update()
{
	if (lives < 0)
	{
		sceneSpeed = 8.0f;
	}

	keyboard->GetDeviceState();
	PressedKeys keys = keyboard->GetKeys();
	playerCar->Move(keys);
	ShiftRoad();

	if (timer->GetTime() > 0.001f)
	{
		if (IsRoadHere(playerCar->Getxy().x, playerCar->Getxy().y))
		{
			score++;
		}
		timer->StartTimer();
	}

	plantOffset += sceneSpeed;
	float delta = plantOffset - ((float)GameLevel::WIN_HEIGHT / (float) NUM_SQUARE_Y);
	if (delta > 0)
	{
		// Reset the plant y coord offset to 0 and adjust the plants in the vector
		//plantOffset = 0;
		plantOffset = plantOffset - ((float) GameLevel::WIN_HEIGHT / (float) NUM_SQUARE_Y);
		UpdatePlants();
	}

	//Check for collisions
	if (CheckPlayerCollision())
	{
		// If the player has collided with something, check that they are not already in a collison.
		// If so, a life is lost.
		if (!inCollision)
		{
			lives--;
			
			// Play different music if the number of lives is now 1
			if (lives == 1)
			{ 
				audioComponent->StopSoundEvent(*levelMusic);
				audioComponent->PlaySoundEvent(*dangerMusic);
			}
		}
		//score = 0;
		inCollision = true;
	}
	else
	{
		// If the player is not in a collision with anything, set the inCollision to false
		// only if the player was previously in a collision
		if (inCollision)
		{
			inCollision = false;
		}
	}
}


/* 
	Method:			Render()
	Description:	This method renders the screen 
*/
void Level1::Render()
{
	//gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	gfx->ClearScreen(0.05f, 0.2f, 0.0f);
	DrawRoad();
	RenderPlants();
	playerCar->DrawSprite();
	DrawScore();
	DrawLives();

	
}


void Level1::DrawScore()
{
	// Retrieve the size of the render target.
	D2D1_SIZE_F renderTargetSize = gfx->GetRenderTarget()->GetSize();

	WCHAR scoreText[256]; 
	_itow_s(score, scoreText, 256, 10);
	gfx->GetRenderTarget()->DrawText(
		scoreText,
		wcslen(scoreText),
		gfx->TextFormatCenter(),
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		gfx->WhiteBrush()
	);


}


void Level1::DrawLives()
{
	// Retrieve the size of the render target.
	D2D1_SIZE_F renderTargetSize = gfx->GetRenderTarget()->GetSize();

	WCHAR livesText[256];
	swprintf(livesText, 256, L"%s%d", L"Lives: ", lives);
	//_itow_s(lives, livesText, 256, 10);

	gfx->GetRenderTarget()->DrawText(
		livesText,
		wcslen(livesText),
		gfx->TextFormatUpperLeftCorner(),
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		gfx->WhiteBrush()
	);
}



/*
	Method:			PlacePlants()
	Description:	This method handles drawing plants in the window. The placement depends on 
					the the information in plantSquares. 
*/
void Level1::RenderPlants()
{
	float x = 0;	// x coord
	float y = 0;	// y coord
	int plantNum = -1;	// the index for the plant asset

	for (int i = 0; i < plantSquares.size(); i++)	// for all the valid plant grid squares...
	{
		plantNum = plantSquares[i].plant;
		
		if (plantNum > -1 && plantSquares[i].render)
		{
			// If there is an index value, get the x and y coordinates and draw it to the screen
			x = plantSquares[i].x;
			y = plantSquares[i].y + plantOffset;
			plants[plantNum]->DrawChromakey(x, y);
		}
	}

	//plantOffset += sceneSpeed;
	//if (plantOffset > GameLevel::WIN_HEIGHT / NUM_VISIBLE_SQUARE_Y)
	//{
	//	// Reset the plant y coord offset to 0 and adjust the plants in the vector
	//	//plantOffset = 0;
	//	plantOffset = plantOffset - (GameLevel::WIN_HEIGHT / NUM_VISIBLE_SQUARE_Y);
	//	UpdatePlants();
	//}
}


/*
	Method:			InitPlants()
	Description:	This method determines the plant placement at the start. If grid position will contain a 
					plant using a 1 in 20 probability and places that information in plantSquares. The index
					of the plant asset is set, if no plant is to be placed, -1 is set.
	*/
void Level1::InitPlants()
{
	std::uniform_int_distribution<int> distribution(0, 19);	// 1 in 20 chance of having a plant in the square
	std::uniform_int_distribution<int> whichPlant(0, 2);	// pick 1 of 3 plants

	int number = 0;

	for (int i = 0; i < plantSquares.size(); i++)
	{
		number = distribution(generator);	// pick the number
		if (number == 0)	// 1 in 20 chance of picking 0
		{
			plantSquares[i].plant = whichPlant(generator);	// randomly pick a plant asset for the square
			plantSquares[i].render = !IsRoadHere(plantSquares[i].x, plantSquares[i].y);
		}
		else
		{
			plantSquares[i].plant = -1;	// -1 for no plant asset
			plantSquares[i].render = false;
		}
	}
}



/* 
	Method:			UpdatePlants()
	Description:	This method determines whether a grid position will contain a plant using
					a 1 in 20 probability and places that information in plantSquares. The index
					of the plant asset is set, if no plant is to be placed, -1 is set.
	*/
void Level1::UpdatePlants()
{
	// Set each row to the previous rows' values
	for (int i = plantSquares.size() - NUM_SQUARE_X - 1; i >= 0; i--)
	{
		plantSquares[i + NUM_SQUARE_X].plant = plantSquares[i].plant;
		plantSquares[i + NUM_SQUARE_X].render = plantSquares[i].render;
	}

	// Set up the first rows' values
	std::uniform_int_distribution<int> distribution(0, 19);	// 1 in 20 chance of having a plant in the square
	std::uniform_int_distribution<int> whichPlant(0, 2);	// pick 1 of 3 plants
	int number = 0;

	for (int i = 0; i < NUM_SQUARE_X; i++)
	{
		number = distribution(generator);	// pick the number
		if (number == 0)	// 1 in 20 chance of picking 0
		{
			plantSquares[i].plant = whichPlant(generator);	// randomly pick a plant asset for the square
			plantSquares[i].render = !IsRoadHere(plantSquares[i].x, plantSquares[i].y);
		}
		else
		{
			plantSquares[i].plant = -1;	// -1 for no plant asset
			plantSquares[i].render = false;
		}
	}
}



/*
	Method:			SetupGrid()
	Description:	This method determines the pixel positions that plants can be placed
					in the window. It uses a 10x10 grid of squares and the position refers to 
					the upper left corner of the squares. 
*/
void Level1::SetupGrid()
{
	// There is a plant in every grid square, whether it will be rendered is determined in the
	// PlacePlants() function

	int w = GameLevel::WIN_WIDTH / NUM_SQUARE_X;	// width in pixels of a square
	int h = GameLevel::WIN_HEIGHT / NUM_SQUARE_Y;	// height in pixels of a square

	//// Place the first row into the vector, this row is entirely offscreen to start with
	//for (int col = 0; col < NUM_SQUARE_X; col++)
	//{
	//	// Make a PlantSquare object with the pixel position and put it in the plantSquares vector
	//	PlantSquare ps = { w*(float)col, h*(float)(-1), -1 };
	//	plantSquares.push_back(ps);
	//}

	//// Place the rest of the rows
	//for (int row = 0; row < NUM_SQUARE_Y; row++)	// for all the rows...
	//{
	//	for (int col = 0; col < NUM_SQUARE_X; col++)
	//	{
	//		// Make a PlantSquare object with the pixel position and put it in the plantSquares vector
	//		PlantSquare ps = { w*(float)col, h*(float)row, -1 };
	//		plantSquares.push_back(ps);
	//	}
	//}

	for (int row = 0; row < NUM_SQUARE_Y + 1; row++)	// for all the rows...
	{
		for (int col = 0; col < NUM_SQUARE_X; col++)
		{
			// Make a PlantSquare object with the pixel position and put it in the plantSquares vector
			PlantSquare ps = { w*(float)col, h*(float)(row - 1), -1 };
			plantSquares.push_back(ps);
		}
	}
}



bool Level1::IsRoadHere(float gridx, float gridy)
{
	float leftx, rightx;
	float gridxRight = gridx + (GameLevel::WIN_WIDTH / NUM_SQUARE_X);
	int i = (int)gridy + (GameLevel::WIN_HEIGHT / NUM_SQUARE_Y);
	int endCrit = i + (GameLevel::WIN_HEIGHT / NUM_SQUARE_Y);
	if (endCrit > roadDims.size())
	{
		endCrit = roadDims.size();
	}

	// the inputs are upper left corner of grid square based on grid squares
	// The roads is drawn one line per pixel height, look at first grid squares worth
	// of road dimensions. Check if the gridx values fall on the line.
	for (i; i < endCrit; i++)
	{
		leftx = roadDims[i];
		rightx = leftx + ROAD_WIDTH;
		if ((gridx > leftx && gridx < rightx) || (gridxRight > leftx && gridxRight < rightx))
		{
			return true;
		}
	}

	return false;
}

bool Level1::CheckPlayerCollision()
{
	bool result = false;

	// If there is a plant sqare in the square, check to see if the player sprite has collided
	for (int i = 0; i < plantSquares.size(); i++)
	{
		if (plantSquares[i].plant > -1 && plantSquares[i].render == true)
		{
			int hitIndex = plantSquares[i].plant;
			HitBox hitbox = { 0,0,0,0 };
			hitbox.upperx = plantSquares[i].x + plantInfo[hitIndex].hitOffsetx;
			hitbox.uppery = plantSquares[i].y + plantInfo[hitIndex].hitOffsety + plantOffset;
			hitbox.lowerx = plantSquares[i].x + plantInfo[hitIndex].hitOffsetx + plantInfo[hitIndex].hitWidth;
			hitbox.lowery = plantSquares[i].y + plantInfo[hitIndex].hitOffsety + plantInfo[hitIndex].hitHeight + plantOffset;
			result = CollisionDetector::CollisionCheck(playerCar->GetHitBox(), hitbox);
			if (result) return true;
		}
	}
	return false;
}

/*
	Method:			DrawRoad()
	Description:	Draws the background road and grass. The road semi-randomly curves. 
*/
void Level1::DrawRoad()
{
	float y = 0;
	D2D1_POINT_2F point1;
	point1.y = y;
	D2D1_POINT_2F point2;
	point2.y = y;

	//int i = (int)GameLevel::WIN_HEIGHT / 10;
	for (int i = 0; y < GameLevel::WIN_HEIGHT; i++)
	/*for (i; i < GameLevel::WIN_HEIGHT/sceneSpeed; i++)*/
	//for (i; i < GameLevel::WIN_HEIGHT + i - 1; i++)
	{
		y += (float)sceneSpeed;
		point1.x = roadDims[i];
		//point1.y++;
		point1.y = y;
		point2.x = point1.x + ROAD_WIDTH;
		//point2.y++;
		point2.y = y;
		gfx->GetRenderTarget()->DrawLine(
			point1,
			point2,
			gfx->GrayBrush(),
			//1.0f
			(float)sceneSpeed
		);
	}


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
int Level1::GetChoice(int numChoices)
{
	std::uniform_int_distribution<int> whichChoice(0, numChoices - 1);	// pick 1 of numChoice choices
	return whichChoice(generator);
}


/*
	Method:		InitRoad()
	Description:
		Initializes the road dimensions for drawing to the string. The road starts in the middle.
*/
void Level1::InitRoad()
{
	for (int i = 0; i < (GameLevel::WIN_HEIGHT * 1.1 ); i++)
	{
		roadDims.push_back(ROAD_STARTING_X);
	}
	//SetNewCurve(0);
	SetNewCurve();
}


/*
	Method:		ShiftRoad()
	Description:
		Adds the next x value to the road dimensions deque. Shifts the values down.
*/
void Level1::ShiftRoad()
{
	// Check if we continue with the current bend/straight-a-way or choose a new one
	float nextx = roadDims[0] + bendValue;

	if ((bendValue < 0 && nextx <= targetLeftx)	||
		(bendValue > 0 && nextx >= targetLeftx) ||
		(bendValue == 0 && straightLength <= 0))
	{
		SetNewCurve();
		nextx = roadDims[0] + bendValue;
	}

	// Put the new value into the deque
	roadDims.push_front(nextx);
	roadDims.pop_back();

	if (bendValue == 0)
	{
		straightLength -= 1;
	}
}


/*
	Method:		Level1::SetNewCurve()
*/
void Level1::SetNewCurve() 
{
	// Right now the road tends to stay straight
	float tempTarget = RandNumber(ROAD_LEFT_X_LEFTMOST, ROAD_LEFT_X_RIGHTMOST, 100);

	if (tempTarget - targetLeftx > MIN_X_OFFSET) // go left
	{
		bendValue = RandNumber(MIN_BEND, MAX_BEND, BEND_INTERVAL) * -1.0f;
	}
	else if ((tempTarget - targetLeftx)*(-1) > MIN_X_OFFSET) // go right
	{
		bendValue = RandNumber(MIN_BEND, MAX_BEND, BEND_INTERVAL);
	}
	else // go straight
	{
		// set the bend value and road length
		bendValue = 0;
		straightLength = RandNumber(MIN_STRAIGHT, MAX_STRAIGHT, STRAIGHT_INTERVAL);
	}

	targetLeftx = tempTarget;
}


/*
	Method:		RandNumber(float min, float max, int interval)
*/
float Level1::RandNumber(float min, float max, int interval)
{
	float result = min + ((rand() % interval) * (max - min)) / interval;
	return result;
}




