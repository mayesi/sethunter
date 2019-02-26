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
	background = new SpriteSheet((wchar_t*)L"background.bmp", gfx);
	playerCar = new PlayerCar(carStartx, carStarty, gfx);
	plants[0] = new SpriteSheet((wchar_t*)L"tree1.bmp", gfx);
	plants[0]->AddChromakey();
	plants[1] = new SpriteSheet((wchar_t*)L"tree2.bmp", gfx);
	plants[1]->AddChromakey();
	plants[2] = new SpriteSheet((wchar_t*)L"shrub1.bmp", gfx);
	plants[2]->AddChromakey();

	// construct a trivial random generator engine from a time-based seed:
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator.seed(seed);
	
	SetupGrid();
	UpdatePlants();
}


/* 
	Method:			Unload()	
	Description:	This method unloads resources 
*/
void Level1::Unload()
{
	delete background;
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
	playerCar->Move(5.0);
	if (playerCar->Getxy().y >= carStarty) {
		UpdatePlants();
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
	//background->Draw();
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
	int w = GameLevel::WIN_WIDTH/numSquareX;	// width in pixels of a square
	int h = GameLevel::WIN_HEIGHT/numSquareY;	// height in pixels of a square

	for (int row = 0; row < numSquareY; row++)	// for all the rows...
	{
		for (int col = 0; col < numSquareX; col++)
		{
			if (col < 3 || col > (numSquareX - 3))	// only do the edges
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
	Description:	Draws the background image. This is a non-moving image that is two colours.
*/
void Level1::DrawRoad()
{
	// Draws a straight road in the middle of the screen
	float leftx = GameLevel::WIN_WIDTH / 10 * 3;
	float rightx = GameLevel::WIN_WIDTH / 10 * 7;
	float y = 0;
	D2D1_POINT_2F point1 = { leftx, y };
	D2D1_POINT_2F point2 = { rightx, y };

	for (int i = 0; i < GameLevel::WIN_HEIGHT; i++)
	{
		point1.y++;
		point2.y++;
		gfx->GetRenderTarget()->DrawLine(
			point1,
			point2,
			gfx->GrayBrush(),
			1.0f
		);
	}

}