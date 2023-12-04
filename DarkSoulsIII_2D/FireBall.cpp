#include "FireBall.h"

FireBall::FireBall(float x, float y, Game* game) :
	Projectile("res/actors/weapons/fire_ball.png", x, y, 32, 32, game) {
	damage = 75;
}

void FireBall::update() {
	Projectile::update();
}

void FireBall::draw(float scrollX, float scrollY)
{

	Projectile::draw(scrollX, scrollY);
}