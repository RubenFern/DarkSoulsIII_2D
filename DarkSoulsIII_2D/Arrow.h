#pragma once

#include "Projectile.h"

class Arrow : public Projectile
{
public:
	Arrow(string filename, float x, float y, int w, int h, Game* game);
	void update() override;
};

