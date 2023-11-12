#include "Arrow.h"

Arrow::Arrow(string filename, float x, float y, int w, int h, Game* game) :
	Projectile("res/actors/weapons/arrow/" + filename, x, y, w, h, game) {
}


void Arrow::update() {
	x += vx;
	y += vy;
}