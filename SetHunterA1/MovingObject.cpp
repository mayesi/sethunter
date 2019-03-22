#include "MovingObject.h"

/*
	Method:			Getxy()
	Description:
		Returns the x and y coordinates of the object on the screen
	Return:
		D2D1_POINT_2F point - the x and y coordinates in a D2D1_POINT_2F structure
*/
D2D1_POINT_2F MovingObject::Getxy()
{
	D2D1_POINT_2F point = { x, y };
	return point;
}


/*
	Method:			GetBoundary()
	Description:
		Returns the boundary of where the object can go on the screen.
	Return:
		Boundary bounds - the boundary of where the object can go on the screen.
*/
Boundary MovingObject::GetBoundary()
{
	return bounds;
}
