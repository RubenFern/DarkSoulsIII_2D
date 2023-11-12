#include "Projectile.h"

Projectile::Projectile(string filename, float x, float y, int w, int h, Game* game) :
	Actor(filename, x, y, w, h, game) {
	vx = 9;
	vy = 0;
}

void Projectile::update() {}