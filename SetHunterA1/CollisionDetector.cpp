#include "CollisionDetector.h"



CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

// True - collision detected
bool CollisionDetector::CollisionCheck(HitBox box1, HitBox box2)
{
	return (box1.upperx < box2.lowerx &&
		box1.lowerx > box2.upperx &&
		box1.uppery < box2.lowery &&
		box1.lowery > box2.uppery);
}
