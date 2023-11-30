#pragma once

#include "Consumable.h"

class EstusFlask : public Consumable
{
public:
	EstusFlask(float x, float y, Game* game);
	void consume() override;
	int restore = 50;
};

