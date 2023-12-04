#include "Attack.h"

Attack::Attack(string filename, int width[4], int height[4], int totalFrames, Game* game)
{
	this->game = game;

	aAttackingRight = new Animation("res/actors/bosses/" + filename + "/right.png", width[0], height[0], width[0] * totalFrames, height[0], 4, totalFrames, false, game);
	aAttackingLeft = new Animation("res/actors/bosses/" + filename + "/left.png", width[1], height[1], width[1] * totalFrames, height[1], 4, totalFrames, false, game);
	aAttackingUp = new Animation("res/actors/bosses/" + filename + "/up.png", width[2], height[2], width[2] * totalFrames, height[2], 4, totalFrames, false, game);
	aAttackingDown = new Animation("res/actors/bosses/" + filename + "/down.png", width[3], height[3], width[3] * totalFrames, height[3], 4, totalFrames, false, game);
}

Projectile* Attack::attack(int x, int y, int orientation)
{
	return NULL;
}