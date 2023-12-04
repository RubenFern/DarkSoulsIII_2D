#pragma once

#include "Tile.h"
#include "Animation.h"
#include "Player.h"

class Barrel : public Tile
{
public:
	Barrel(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	int destroy(Player* player);

	Animation* animation;
};

