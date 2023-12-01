#pragma once

// IDLE
#define WIDTH_IDLE_U_L_R 34
#define WIDTH_IDLE_D 36

#define HEIGHT_IDLE_U_L_R 53
#define HEIGHT_IDLE_D 54

// WALK
#define WIDTH_WALK_D 45
#define WIDTH_WALK_L_R 51
#define WIDTH_WALK_U 56

#define HEIGHT_WALK_D 54
#define HEIGHT_WALK_L_R 54
#define HEIGHT_WALK_U 54

// ATTACK
#define WIDTH_ATTACK_D 40
#define WIDTH_ATTACK_L_R 51
#define WIDTH_ATTACK_U 41

#define HEIGHT_ATTACK_D 54
#define HEIGHT_ATTACK_L_R 60
#define HEIGHT_ATTACK_U 61

// DEATH
#define WIDTH_DEATH 41
#define HEIGHT_DEATH 54

#include "Enemy.h"
#include "Animation.h"
#include "Arrow.h"
#include "Projectile.h"

class Archer : public Enemy
{
public:
	Archer(float x, float y, Game* game);
	Projectile* attack() override;
	int attackCadence = 120;
};
