#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"

/*
	The boundary of where the object can be placed on the screen in pixels, 0 means no boundary
*/
typedef struct Boundary
{
	float left;		// from the left side	
	float right;	// from the right side
	float upper;	// from the top
	float lower;	// from the bottom
} Boundary;


/*
	Class:		MovingObject
	Description:
		This is an abstract class that describes a basic moving object
*/
class MovingObject
{
protected:
	SpriteSheet* sprite;
	float x;
	float y;
	Boundary bounds;

public:
	// Getters and Setters for the private members
	D2D1_POINT_2F Getxy();
	Boundary GetBoundary();

	virtual ~MovingObject() { };	// Destructor
	virtual void Move() = 0;		// Method to update the objects' position
	virtual void DrawSprite() = 0;	// Method to draw the sprite
	virtual void SetBoundary(Boundary bounds) = 0;	// Method to set where the object can go on the screen
};

