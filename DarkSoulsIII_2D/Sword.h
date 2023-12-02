#pragma once

#include "Projectile.h"

class Sword : public Projectile
{
public:
	Sword(float x, float y, Game* game);
	void update() override;

	int lifeTime = 8;
};

