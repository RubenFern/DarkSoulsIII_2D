#pragma once

#include "Actor.h"

class Weapon : public Actor
{
public:
	Weapon(string filename, float x, float y, int width, int height, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	string path;
	int damage;
	int attackCadence = 30;
	int attackTime = 0;
};

