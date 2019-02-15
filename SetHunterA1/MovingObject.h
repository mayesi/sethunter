#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"

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

public:
	// Getters and Setters for the private members
	//virtual void Setxy() = 0;
	//virtual void SetSprite() = 0;
	//virtual D2D1_POINT_2F Getxy() = 0; // don't need this?
	//virtual SpriteSheet* GetSprite() = 0;	// don't need this?
	virtual ~MovingObject() { };	// Destructor
	virtual void Move() = 0;	// Method to update the objects' position
	virtual void DrawSprite() = 0;		// Method to draw the sprite
};