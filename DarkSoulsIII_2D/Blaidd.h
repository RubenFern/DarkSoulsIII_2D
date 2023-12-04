#pragma once

#define ATTACK_DISTANCE 40
#define TIME_CHANGE_ATTACK 100
#define ATTACK_CADENCE 40
#define ATTACKS 3

#include "Enemy.h"
#include "Attack.h"
#include "Circular.h"

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

