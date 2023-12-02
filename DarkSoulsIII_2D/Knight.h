#pragma once

#define ATTACK_DISTANCE 40

#define WIDTH_WALK_L_R 53
#define HEIGHT_WALK_L_R_U_D 58
#define WIDTH_WALK_U 45
#define WIDTH_WALK_D 41

#define WIDTH_ATTACK_L 104
#define HEIGHT_ATTACK_L 60
#define WIDTH_ATTACK_R 103
#define HEIGHT_ATTACK_R 57
#define WIDTH_ATTACK_U 83
#define HEIGHT_ATTACK_U 70
#define WIDTH_ATTACK_D 83
#define HEIGHT_ATTACK_D 76

#define WIDTH_DEATH 49
#define HEIGHT_DEATH 57

#include "Enemy.h"
#include "Sword.h"

class Knight : public Enemy
{
public:
	Knight(float x, float y, Game* game);
	Projectile* attack() override;

	int attackCadence = 40;
};

