#include "FireKeeper.h"

FireKeeper::FireKeeper(float x, float y, Game* game)
	: Actor("res/actors/firekeeper/idle/down.png", x, y, 37, 53, game) {

	orientation = game->orientationDown;
	state = game->stateMoving;

	aIdleRight = new Animation("res/actors/firekeeper/idle/right.png", 32, 51, 32, 51, 6, 1, true, game);
	aIdleLeft = new Animation("res/actors/firekeeper/idle/left.png", 32, 51, 32, 51, 6, 1, true, game);
	aIdleUp = new Animation("res/actors/firekeeper/idle/up.png", 32, 50, 32, 50, 6, 1, true, game);
	aIdleDown = new Animation("res/actors/firekeeper/idle/down.png", 32, 50, 32, 50, 6, 1, true, game);

	animation = aIdleDown;
}

void FireKeeper::update() 
{
	if (orientation == game->orientationRight)
		animation = aIdleRight;
	else if (orientation == game->orientationLeft)
		animation = aIdleLeft;
	else if (orientation == game->orientationUp)
		animation = aIdleUp;
	else if (orientation == game->orientationDown)
		animation = aIdleDown;
}

void FireKeeper::draw(float scrollX, float scrollY)
{
	animation->draw(x - scrollX, y - scrollY);
}