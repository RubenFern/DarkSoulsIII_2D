#pragma once

#include "Tile.h"
#include "Animation.h"

class Bonfire : public Tile
{
public:
	Bonfire(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;

	Animation* animation;
};