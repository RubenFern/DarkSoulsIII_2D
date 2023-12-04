#pragma once

#include "Actor.h"
#include "Text.h"

class Consumable : public Actor
{
public:
	Consumable(string filename, float x, float y, int width, int height, Game* game);
	virtual void draw(float scrollX = 0, float scrollY = 0) override;
	virtual void consume();
	virtual void update();
	Text* text;
	int num = 0;
	string name;
	string pathImage;
};