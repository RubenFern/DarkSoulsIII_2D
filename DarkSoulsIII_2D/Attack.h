#pragma once

#include "Animation.h"
#include "Game.h"
#include "Projectile.h"

class Attack
{
public:
	Attack(string filename, int width[4], int height[4], int totalFrames, Game* game);	// Width/Height -> Right, Left, Up, Down
	virtual Projectile* attack(int x, int y, int orientation);

	int distanceAttack = 0;
	int damage = 0;
	int cadence = 0;

	Game* game;
	Animation* aAttackingRight;
	Animation* aAttackingLeft;
	Animation* aAttackingUp;
	Animation* aAttackingDown;
	Projectile* projectile;
};

