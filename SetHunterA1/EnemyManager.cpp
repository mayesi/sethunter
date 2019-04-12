#include "EnemyManager.h"

EnemyManager::EnemyManager(Graphics* ingfx)
{
	// Set up the spritesheet for the enemy car
	gfx = ingfx;
	enemyCarSprite = new SpriteSheet(carImage, gfx);
	enemyCarSprite->AddChromakey();
}


EnemyManager::~EnemyManager()
{
	delete enemyCarSprite;
}


void EnemyManager::SpawnEnemy(float startx, float starty, float startSpeed)
{
	// Spawns an enemy at the position provided
	if (numActive < MAX_NUM_ENEMIES)
	{
		// The maximum number of enemies has NOT been reached, can make active enemies
		// Check if there is room to add to the vector
		if (enemyObjects.size() < MAX_NUM_ENEMIES)
		{
			// Can add a new enemy to the vector
			EnemyCar* enemy = new EnemyCar(enemyCarSprite);
			EnemyInfo info = { enemy, true };
			enemyObjects.push_back(info);
		}
		else
		{
			// Cycle through the enemy list to find an inactive one, make it active
			bool found = false;
			int i = 0;
			while (!found && i < enemyObjects.size())
			{
				if (!enemyObjects[i].active)
				{
					enemyObjects[i].active = true;
					enemyObjects[i].enemy->SetXY(startx, starty);
					enemyObjects[i].enemy->SetSpeed(startSpeed);
					found = true;
				}
			}
		}
	}
	
}


void EnemyManager::MoveEnemies()
{
	for (int i = 0; i < enemyObjects.size(); i++)
	{
		if (enemyObjects[i].active)
		{
			enemyObjects[i].enemy->Move();
		}
	}
}


void EnemyManager::RenderEnemies()
{
	for (int i = 0; i < enemyObjects.size(); i++)
	{
		if (enemyObjects[i].active)
		{
			enemyObjects[i].enemy->DrawSprite();
		}
	}
}


bool EnemyManager::CheckEnemyCollisions(HitBox box1)
{
	for (int i = 0; i < enemyObjects.size(); i++)
	{
		if (enemyObjects[i].active)
		{
			if (CollisionDetector::CollisionCheck(box1, enemyObjects[i].enemy->GetHitBox())) return true;
		}
	}
	return false;
}



