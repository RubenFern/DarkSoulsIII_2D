#pragma once

#include "Consumable.h"

class BloodGem : public Consumable
{
public:
	BloodGem(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void consume() override;
	int useTime = 3000;
};

