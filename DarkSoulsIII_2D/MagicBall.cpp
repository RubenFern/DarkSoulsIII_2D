#include "MagicBall.h"

MagicBall::MagicBall(float x, float y, Game* game) :
	Projectile("res/actors/weapons/magic_ball.png", x, y, 32, 32, game) {
	damage = 75;
}

void MagicBall::update() {
	Projectile::update();
}

void MagicBall::draw(float scrollX, float scrollY) 
{
	if (timeLapse > 0) 
	{
		timeLapse--;
		return;
	}

	Projectile::draw(scrollX, scrollY);
}