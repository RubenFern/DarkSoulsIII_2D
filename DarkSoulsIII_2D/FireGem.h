#pragma once

#define TIME 2000

#include "Consumable.h"
#include "UchigatanaBleeding.h"

class FireGem : public Consumable
{
public:
	FireGem(float x, float y, Game* game);
	void consume() override;
	void update() override;
	int useTime = TIME;
	bool isUsing = false;
};

