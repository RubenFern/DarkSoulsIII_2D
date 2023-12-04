#pragma once

#include "Attack.h"
#include "Game.h"
#include "Sword.h"

class Thrust : public Attack
{
public:
	Thrust(Game* game);
	Projectile* attack(int x, int y, int orientation) override;
};
