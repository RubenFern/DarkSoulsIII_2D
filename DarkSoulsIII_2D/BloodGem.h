#pragma once

#define TIME 500

#include "Consumable.h"
#include "UchigatanaBleeding.h"

class BloodGem : public Consumable
{
public:
	BloodGem(float x, float y, Game* game);
	void consume() override;
	void update() override;
	int useTime = TIME;
	bool isUsing = false;
};

