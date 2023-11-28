#pragma once

#include "Game.h"

class HealthBar
{
public:
	HealthBar(int health, float x, float y, Game* game);
	void draw();
	int health;
	int x;
	int y;
	int width;
	int height;
	Game* game;
};

