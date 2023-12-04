#pragma once

#include "Animation.h"
#include "Game.h"
#include "Projectile.h"

class Attack
{
public:
	Attack(string filename, int width[4], int height[4], int totalFrames, Game* game);	// Width/Height -> Right, Left, Up, Down
	virtual Projectile* attack(int x, int y, int orientation);

	int damage = 0;
	bool freeze = false;
	int frezzeTime = 40;

	Game* game;
	Animation* aAttackingRight;
	Animation* aAttackingLeft;
	Animation* aAttackingUp;
	Animation* aAttackingDown;
};

