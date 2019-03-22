#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"


/*
	Method:			Load()
	Description:	Loads the sprites and sets up the initial state of the game.
*/
void Level1::Load()
{
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
	UpdatePlants();
	InitRoad();
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
}


/* 
	Method:			Update()
	Description:	This method updates the state of game objects 
*/
void Level1::Update()
{
	//playerCar->Move(5.0);
	//if (playerCar->Getxy().y >= carStarty) {
	//	UpdatePlants();
	//}
	keyboard->GetDeviceState();
	PressedKeys keys = keyboard->GetKeys();
	playerCar->Move(keys);
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
	PlacePlants();
	playerCar->DrawSprite();
}


/*
	Method:			PlacePlants()
	Description:	This method handles drawing plants in the window. The placement depends on 
					the the information in plantSquares. 
*/
void Level1::PlacePlants()
{
	float x = 0;	// x coord
	float y = 0;	// y coord
	int plantNum = -1;	// the index for the plant asset

	for (int i = 0; i < plantSquares.size(); i++)	// for all the valid plant grid squares...
	{
		plantNum = plantSquares[i].plant;
		if (plantNum > -1)
		{
			// If there is an index value, get the x and y coordinates and draw it to the screen
			x = plantSquares[i].x;
			y = plantSquares[i].y;
			plants[plantNum]->DrawChromakey(x, y);
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
	
	std::uniform_int_distribution<int> distribution(0, 19);	// 1 in 20 chance of having a plant in the square
	std::uniform_int_distribution<int> whichPlant(0, 2);	// pick 1 of 3 plants

	int number = 0;

	for (int i = 0; i < plantSquares.size(); i++) 
	{
		number = distribution(generator);	// pick the number
		if (number == 0)	// 1 in 20 chance of picking 0
		{
			plantSquares[i].plant = whichPlant(generator);	// randomly pick a plant asset for the square
		}
		else 
		{
			plantSquares[i].plant = -1;	// -1 for no plant asset
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
	int w = GameLevel::WIN_WIDTH/NUM_SQUARE_X;	// width in pixels of a square
	int h = GameLevel::WIN_HEIGHT/NUM_SQUARE_Y;	// height in pixels of a square

	for (int row = 0; row < NUM_SQUARE_Y; row++)	// for all the rows...
	{
		for (int col = 0; col < NUM_SQUARE_X; col++)
		{
			if (col < 3 || col > (NUM_SQUARE_X - 3))	// only do the edges
			{
				// Make a PlantSquare object with the pixel position and put it in the plantSquares vector
				PlantSquare ps = { (float)w*col, (float)h*row, -1 };
				plantSquares.push_back(ps);
			}
		}
	}
}


/*
	Method:			DrawBackground()
	Description:	Draws the background road and grass. The road semi-randomly curves. 
*/
void Level1::DrawRoad()
{
	//// Draws a straight road in the middle of the screen
	//float leftx = GameLevel::WIN_WIDTH / 10 * 3;
	//float rightx = GameLevel::WIN_WIDTH / 10 * 7;
	//float y = 0;
	//D2D1_POINT_2F point1 = { leftx, y };
	//D2D1_POINT_2F point2 = { rightx, y };

	//for (int i = 0; i < GameLevel::WIN_HEIGHT; i++)
	//{
	//	point1.y++;
	//	point2.y++;
	//	gfx->GetRenderTarget()->DrawLine(
	//		point1,
	//		point2,
	//		gfx->GrayBrush(),
	//		1.0f
	//	);
	//}


	//int curve = GetChoice(3); // 0 - go straight, 1 - go left, 2 - go right

	D2D1_POINT_2F point1;
	point1.y = 0;
	D2D1_POINT_2F point2;
	point2.y = 0;

	for (int i = 0; i < GameLevel::WIN_HEIGHT; i++)
	{
		point1.x = roadDims[i];
		point1.y++;
		point2.x = point1.x + ROAD_WIDTH;
		point2.y++;
		gfx->GetRenderTarget()->DrawLine(
			point1,
			point2,
			gfx->GrayBrush(),
			1.0f
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
	for (int i = 0; i < GameLevel::WIN_HEIGHT; i++)
	{
		roadDims.push_back(ROAD_STARTING_X);
	}
	SetNewCurve();
}


/**/
void Level1::ShiftRoad(int direction)
{
	float nextx = roadDims[0];

	if (direction == 0) // move straight
	{
		roadDims.push_front(nextx);
	}
	else if (direction == 1) // move left
	{
		//nextx -= 
	}
	else if (direction == 2) // move right
	{

	}
	roadDims.pop_back();
}


void Level1::SetNewCurve()
{
	int nextCurve = GetChoice(3); // 0 - go straight, 1 - go left, 2 - go right

	if (nextCurve == 1) // go left
	{
		bendValue = RandNumber(MIN_BEND, MAX_BEND, BEND_INTERVAL) * -1.0f;
	}
	else if (nextCurve == 2) // go right
	{
		bendValue = RandNumber(MIN_BEND, MAX_BEND, BEND_INTERVAL);
	}
	else // go straight
	{
		bendValue = 0;
	}
}


float Level1::RandNumber(float min, float max, int interval)
{
	float result = min + ((rand() % interval) * (max - min)) / interval;
	return result;
}