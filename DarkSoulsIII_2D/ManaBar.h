#pragma once

#include "Game.h"

class ManaBar
{
public:
	ManaBar(int health, int height, float x, float y, Game* game);
	void draw(int x, int y);
	int mana;
	int height;
	int x;
	int y;
	int width;
	Game* game;
};
