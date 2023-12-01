#pragma once

#include "Game.h"

class HealthBar
{
public:
	HealthBar(int health, int height, float x, float y, Game* game);
	void draw(int x, int y);
	int health;
	int height;
	int x;
	int y;
	int width;
	Game* game;
};

