#include "Projectile.h"

Projectile::Projectile(string filename, float x, float y, int w, int h, Game* game) :
	Actor(filename, x, y, w, h, game) {
	vx = 0;
	vy = 0;
}

void Projectile::update() 
{
	x += vx;
	y += vy;
}