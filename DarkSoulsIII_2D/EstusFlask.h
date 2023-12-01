#pragma once

#include "Consumable.h"
#include "Text.h"

class EstusFlask : public Consumable
{
public:
	EstusFlask(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void consume() override;
	int restore = 50;
	Text* textNumEstus;
	int totalEstus = 10;
	int numEstus = totalEstus;
};

