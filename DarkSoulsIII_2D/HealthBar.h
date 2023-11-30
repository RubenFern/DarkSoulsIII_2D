#pragma once

#include "Game.h"

class HealthBar
{
public:
	HealthBar(int health, int height, float x, float y, Game* game);
	void draw();
	int health;
	int height;
	int x;
	int y;
	Game* game;
};

