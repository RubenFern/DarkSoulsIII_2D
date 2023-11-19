#include "Sword.h"

Sword::Sword(string filename, float x, float y, int w, int h, Game* game) :
	Projectile("res/disparo_jugador.png", x, y, w, h, game) {
}

void Sword::update() {
	Projectile::update();

	lifeTime--;
}