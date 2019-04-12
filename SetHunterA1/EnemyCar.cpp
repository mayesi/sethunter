#include "EnemyCar.h"



EnemyCar::EnemyCar(SpriteSheet* initSprite)
{

	speed = defaultSpeed;
	sprite = initSprite;
}

EnemyCar::~EnemyCar()
{
	delete sprite;
}

void EnemyCar::Move()
{
	y += speed;
}

void EnemyCar::DrawSprite()
{
	sprite->DrawChromakey(x, y);
}

void EnemyCar::SetBoundary(Boundary bounds)
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

void EnemyCar::SetHitBox()
{
	hitbox.upperx = x + hitOffsetx;
	hitbox.uppery = y + hitOffsety;
	hitbox.lowerx = x + hitOffsetx + hitWidth;
	hitbox.lowery = y + hitOffsety + hitHeight;
}

HitBox EnemyCar::GetHitBox()
{
	return hitbox;
}

void EnemyCar::SetXY(float initx, float inity)
{
	x = initx;
	y = inity;
}

void EnemyCar::SetSpeed(float initSpeed)
{
	if (initSpeed >= 0)
	{
		speed = initSpeed;
	}
	else
	{
		speed = 0;
	}
}
