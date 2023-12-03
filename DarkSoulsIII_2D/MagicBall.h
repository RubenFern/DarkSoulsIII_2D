#pragma once

#include "Projectile.h"

class MagicBall : public Projectile
{
public:
	MagicBall(float x, float y, Game* game);
	void update() override;
	void draw(float scrollX = 0, float scrollY = 0) override;

	int timeLapse = 10;
};

