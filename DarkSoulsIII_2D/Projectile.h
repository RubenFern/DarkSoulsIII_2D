#pragma once

#include "Actor.h"


class Projectile : public Actor
{
public:
	Projectile(string filename, float x, float y, int w, int h, Game* game);
	virtual void update();
	int damage;
};