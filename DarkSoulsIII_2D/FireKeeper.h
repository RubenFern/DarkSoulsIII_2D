#pragma once

#include "Actor.h"
#include "Animation.h"

class FireKeeper : public Actor
{
public:
	FireKeeper(float x, float y, Game* game);
	void update();
	void draw(float scrollX = 0, float scrollY = 0) override;
	int orientation;
	int state;
	bool isUpLevel = false;

	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aIdleUp;
	Animation* aIdleDown;

	Animation* animation;
};

