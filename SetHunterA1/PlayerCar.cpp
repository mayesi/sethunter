#include "PlayerCar.h"
#include "Graphics.h"

/*
	Method:			PlayerCar()
	Description:
		Constructor for the PlayerCar class
	Parameters:
		float initx - the starting x coordinate for the object on the screen
		float inity - the starting y coordinate for the object on the screen
		Graphics* gfx - the Graphics object that will do the rendering
*/
PlayerCar::PlayerCar(float initx, float inity, Graphics* gfx)
{
	sprite = new SpriteSheet(carImage, gfx);
	sprite->AddChromakey();
	x = initx;
	y = inity;
	startingy = inity;
}


/*
	Method:			~PlayerCar()
	Description:
		Destructor for the PlayerCar class. Releases SpriteSheet resources.
*/
PlayerCar::~PlayerCar()
{
	delete sprite;
}


/*
	Method:			Move()
	Description:
		This method updates the x and y coordinates of the object on the screen. The movement
		'behaviour' is defined in the Move(float speed) method. Uses a default movement speed.
*/
void PlayerCar::Move()
{
	PlayerCar::Move(1.0);
}



/* 
	Method:			Move()
	Description:
		This method updates the x and y coordinates of the object on the screen. The movement
		'behaviour' is defined in this method.
*/
void PlayerCar::Move(float speed)
{
	// So far, the car only moves up the screen, then restarts at the bottom of the screen
	float tempy = y - speed;
	if (tempy <= 0) {
		y = startingy;
	}
	else {
		y = tempy;
	}
}


/* 
	Method:			Getxy()
	Description:
		Returns the x and y coordinates of the car on the screen
	Return:
		D2D1_POINT_2F point - the x and y coordinates in a D2D1_POINT_2F structure
*/
D2D1_POINT_2F PlayerCar::Getxy()
{
	D2D1_POINT_2F point = { x, y };
	return point;
}


/*
	Method:			DrawSprite()
	Description:	
		This method draws the sprite on the screen
*/
void PlayerCar::DrawSprite()
{
	sprite->DrawChromakey(x, y);
}
