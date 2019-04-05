#pragma once
#include "MovingObject.h"
#include "KeyboardInput.h"

/* 
	Class:			PlayerCar
	Description:	This class has the logic for the player's car behaviour and image
*/
class PlayerCar : public MovingObject
{
private:
	const float defaultSpeed = 5.0f;
	const Boundary defaultBoundary = { 0.0f, 80.0f, 20.0f, 100.0f };
	const float defaultAccelRate = 0.2f;
	const float defaultTopSpeed = 10.0f;
	
	wchar_t* carImage = (wchar_t*)L"playercar.bmp";	// the bmp file name for the car image
	float startingx;		// This is the x position that the car starts from when the screen resets
	float startingy;		// This is the y position that the car starts from when the screen resets
	PressedKeys lastSet;	// The last set of keys pressed
	float speed;			// The current speed
	float topSpeed;			// The top speed
	float accelRate;		// The acceleration/deceleration rate
	Graphics* gfx;			// use this?

	void Accelerate();		// Increases the speed
	void Decelerate();		// Decreases the speed

public:
	
	PlayerCar(float initx, float inity, Graphics * gfx);	// Constructor
	~PlayerCar();			// Destructor

	void Move();			// 'Moves' the car by calling the other move method with a default speed
	void Move(float speed);	// 'Moves' the car to it's new screen position
	void Move(PressedKeys keys);	// 'Moves' the car based on current speed and which keys are pressed

	void DrawSprite();		// Draws the image to the screen
	//D2D1_POINT_2F Getxy();	// Returns the coordinates of the car on the screen
	void SetBoundary(Boundary bounds);	// Set the boundaries for car movement
	void SetTopSpeed(float top);		// Set the object's top speed
	float GetSpeed();		// Get the object's current speed
};