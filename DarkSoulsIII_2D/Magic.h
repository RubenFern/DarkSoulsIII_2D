#pragma once

#include "Attack.h"
#include "Game.h"
#include "FireBall.h"

class Magic : public Attack
{
public:
	Magic(Game* game);
	Projectile* attack(int x, int y, int orientation) override;
};
