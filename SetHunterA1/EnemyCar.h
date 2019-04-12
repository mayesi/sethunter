#pragma once
#include "MovingObject.h"
class EnemyCar :
	public MovingObject
{
private:
	const float defaultSpeed = 5.0f;
	float speed;			// The current speed

	HitBox hitbox;
	const float hitOffsetx = 25.0f;	// from the left side
	const float hitOffsety = 5.0f;	// from the top
	const float hitWidth = 50.0f;
	const float hitHeight = 90.0f;
	
	// the private methods
	void SetHitBox();		// Set the object's hitbox parameters

public:
	EnemyCar(SpriteSheet* initSprite);
	~EnemyCar();

	void Move();
	void DrawSprite();					// Draws the image to the screen
	void SetBoundary(Boundary bounds);	// Set the screen boundaries for movement
	HitBox GetHitBox();					// Gets the hitbox
	void SetXY(float initx, float inity);	// Set the x and y values of the object
	void SetSpeed(float initSpeed);			// Set the speed 
};

