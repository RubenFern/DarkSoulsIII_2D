#pragma once

#define WIDTH_MENU 500
#define HEIGHT_MENU 300
#define STATS 3
#define OPTIONS 4

#include "Actor.h"
#include "Text.h"

class MenuUpLevel : public Actor
{
public:
	MenuUpLevel(Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;

	Text* title;

	Text* options[OPTIONS];
	Text* stats[STATS];
};

