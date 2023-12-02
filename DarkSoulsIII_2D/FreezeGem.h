#pragma once

#define TIME 2000

#include "Consumable.h"
#include "UchigatanaFreezing.h"

class FreezeGem : public Consumable
{
public:
	FreezeGem(float x, float y, Game* game);
	void consume() override;
	void update() override;
	int useTime = TIME;
	bool isUsing = false;
};

