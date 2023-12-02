#include "Sword.h"

Sword::Sword(float x, float y, Game* game) :
	Projectile("", x, y, 20, 20, game) {

	damage = 30;
}

void Sword::update() {
	Projectile::update();

	lifeTime--;
}