#pragma once

#include "Projectile.h"

class Sword : public Projectile
{
public:
	Sword(string filename, float x, float y, int w, int h, Game* game);
	void update() override;

	int lifeTime = 8;
};

