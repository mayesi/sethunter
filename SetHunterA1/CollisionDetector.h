#pragma once

typedef struct HitBox
{
	float upperx;	// the upper left corner x
	float uppery;	// the upper left corner y
	float lowerx;	// the lower right corner x
	float lowery;	// the lower right corner y
};

class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	static bool CollisionCheck(HitBox obj1, HitBox obj2);

	friend class Level1;
};

