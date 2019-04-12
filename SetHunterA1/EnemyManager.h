#pragma once
#include "EnemyCar.h"
#include "CollisionDetector.h"
#include <vector>

typedef struct EnemyInfo
{
	EnemyCar* enemy;	// The enemy object
	bool active;		// whether the object is active, do move/render this object or not
} EnemyInfo;


// Only makes cars
class EnemyManager
{
private:
	Graphics* gfx;	// pointer to a Graphics object

	std::vector<EnemyInfo> enemyObjects;	// holds any spawned enemy cars, the 'manager' uses this
	const int MAX_NUM_ENEMIES = 5;	// the maximum number of enemies to spawn on the screen
	int numActive = 0;
	
	wchar_t* carImage = (wchar_t*)L"enemycar.bmp";	// the bmp file name for the car image
	SpriteSheet* enemyCarSprite;	// the spritesheet for the enemy car objects

public:
	EnemyManager(Graphics* gfx);
	~EnemyManager();

	void SpawnEnemy(float startx, float starty, float startSpeed);	// Creates an active enemy
	void MoveEnemies();								// Move active enemies
	void RenderEnemies();							// Render active enemies
	bool CheckEnemyCollisions(HitBox box1);	// Check if any of the enemies has collided with the hitbox

};

