#pragma once

#define TIME_CHANGE_ATTACK 100
#define ATTACKS 3

#include "Enemy.h"
#include "Attack.h"
#include "Circular.h"
#include "Thrust.h"
#include "Magic.h"
#include "Projectile.h"

class Blaidd : public Enemy
{
public:
	Blaidd(float x, float y, Game* game);
	Projectile* attack() override;
	void update() override;
	void changeAttack();

	int timeChangeAttack = 100;

	Attack* attacks[ATTACKS];
	Attack* selectedAttack;
};

