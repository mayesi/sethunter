/*
	File:			PlayerCar.cpp
	Author:			Maye Inwood
	First edit:		February 2019
	Latest edit:
	Description:
		Contains the methods for the PlayerCar class.
*/

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
	this->gfx = gfx;
	sprite = new SpriteSheet(carImage, gfx);
	sprite->AddChromakey();
	x = initx;
	y = inity;
	startingy = inity;
	lastSet = { false, false, false, false };
	speed = defaultSpeed;
	bounds = defaultBoundary;
	accelRate = defaultAccelRate;
	topSpeed = defaultTopSpeed;

	// Set the bounding box info
	hitbox.upperx = x + hitOffsetx;
	hitbox.uppery = y;
	hitbox.lowerx = x + hitOffsetx + hitWidth;
	hitbox.lowery = y + hitHeight;
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
	PlayerCar::Move(speed);
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


void PlayerCar::Move(PressedKeys keys)
{ 
	// Move the car to it's new position based on what keys are pressed on the keyboard.
	// If left and right or up and down are pressed simultaneously, do nothing.
	float tempx = x;
	float tempy = y;

	// Compare left and right key presses (a and d)
	if (keys.pressed_left && !keys.pressed_right) // Go left
	{
		tempx = x - defaultSpeed;
	}
	else if (!keys.pressed_left && keys.pressed_right)	// Go right
	{
		tempx = x + defaultSpeed;
	}
	
	// Compare up and down key presses (w and s)
	// Accelerate on up presses and decelerate on down presses
	if (keys.pressed_down && !keys.pressed_up)	// Go down
	{
		Decelerate();
		tempy = y + speed;
	}
	else if (!keys.pressed_down && keys.pressed_up)	// Go up
	{
		Accelerate();
		tempy = y - speed;
	}

	// Set the lastSet to this set of key presses - NOT USING LASTSET RIGHT NOW
	lastSet.pressed_left = keys.pressed_left;
	lastSet.pressed_down = keys.pressed_down;
	lastSet.pressed_down = keys.pressed_down;
	lastSet.pressed_up = keys.pressed_up;

	D2D1_SIZE_F size = gfx->GetRenderTarget()->GetSize();

	if (tempx >= bounds.left && tempx <= (size.width - bounds.right))
	{
		x = tempx;
	}
	if (tempy >= bounds.upper && tempy <= (size.height - bounds.lower))
	{
		y = tempy;
	}

	// Set the hitbox values
	SetHitBox();
}


/*
	Method:		Accelerate()
	Description:
		This function increases the speed by the acceleration rate up to the top speed.
*/
void PlayerCar::Accelerate()
{
	if (speed < topSpeed)
	{
		float tempSpeed = speed + accelRate;
		if (tempSpeed > topSpeed) {
			speed = topSpeed;
		}
		else
		{
			speed = tempSpeed;
		}
	}
}


/*
	Method:		Decelerate()
	Description:
		This function decreases the object's current speed by the acceleration rate.
*/
void PlayerCar::Decelerate()
{
	if (speed > 0) 
	{
		float tempSpeed = speed - accelRate;
		if (tempSpeed < 0)
		{
			speed = 0.0f;
		}
		else
		{
			speed = tempSpeed;
		}
	}
}


///* 
//	Method:			Getxy()
//	Description:
//		Returns the x and y coordinates of the car on the screen
//	Return:
//		D2D1_POINT_2F point - the x and y coordinates in a D2D1_POINT_2F structure
//*/
//D2D1_POINT_2F PlayerCar::Getxy()
//{
//	D2D1_POINT_2F point = { x, y };
//	return point;
//}


/*
	Method:			DrawSprite()
	Description:	
		This method draws the sprite on the screen
*/
void PlayerCar::DrawSprite()
{
	sprite->DrawChromakey(x, y);
}


/*
	Method:			SetBoundary()
	Description:
		You can set the car's movement boundaries using this method.
	Parameter:
		Boundary boundaries - the new boundaries, can use NULL to keep the default/previous setting
*/
void PlayerCar::SetBoundary(Boundary bounds)
{
	if (bounds.left != NULL) 
	{
		this->bounds.left = bounds.left;
	}
	if (bounds.right != NULL) 
	{
		this->bounds.right = bounds.right;
	}
	if (bounds.lower != NULL) 
	{
		this->bounds.lower = bounds.lower;
	}
	if (bounds.upper != NULL)
	{
		this->bounds.upper = bounds.upper;
	}
}


/*
	Method:		SetTopSpeed(float top)
	Description:
		Set's the objects' top speed.
	Parameters:
		float top - the new top speed.
*/
void PlayerCar::SetTopSpeed(float top)
{
	if (top < 0)
	{
		topSpeed = top * -1;
	}
	else
	{
		topSpeed = top;
	}
}


/*
	Method:		GetSpeed()
	Description:
		Returns the objects' current speed.
	Return:
		float speed - the objects' current speed.
*/
float PlayerCar::GetSpeed()
{
	return speed;
}

void PlayerCar::SetHitBox()
{
	hitbox.upperx = x + hitOffsetx;
	hitbox.uppery = y + hitOffsety;
	hitbox.lowerx = x + hitOffsetx + hitWidth;
	hitbox.lowery = y + hitOffsety + hitHeight;
}

HitBox PlayerCar::GetHitBox()
{
	return hitbox;
}
