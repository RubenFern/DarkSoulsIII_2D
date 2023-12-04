#pragma once

#include "Attack.h"
#include "Game.h"
#include "Sword.h"

class Circular : public Attack
{
public:
	Circular(Game* game);
	Projectile* attack(int x, int y, int orientation) override;

	int timeFreeze = 30;
};

