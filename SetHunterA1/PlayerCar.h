#pragma once
#include "MovingObject.h"

/* 
	Class:			PlayerCar
	Description:	This class has the logic for the player's car behaviour and image
*/
class PlayerCar : public MovingObject
{
private:
	wchar_t* carImage = (wchar_t*)L"playercar.bmp";	// the bmp file name for the car image
	float startingy;	// This is the y position that the car starts from when the screen resets

public:
	
	PlayerCar(float initx, float inity, Graphics * gfx);	// Constructor
	~PlayerCar();			// Destructor

	void Move();			// 'Moves' the car by calling the other move method with a default speed
	void Move(float speed);	// 'Moves' the car to it's new screen position

	void DrawSprite();		// Draws the image to the screen
	D2D1_POINT_2F Getxy();	// Returns the coordinates of the car on the screen
	
};