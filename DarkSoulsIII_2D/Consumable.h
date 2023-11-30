#pragma once

#include "Actor.h"

class Consumable : public Actor
{
public:
	Consumable(string filename, float x, float y, int width, int height, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	virtual void consume();
};