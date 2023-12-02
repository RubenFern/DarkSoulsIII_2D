#include "Uchigatana.h"
#include "Sword.h"

Uchigatana::Uchigatana(float x, float y, Game* game) :
	Weapon("res/actors/weapons/uchigatana.jpg", x, y, 60, 80, game)
{
	path = "uchigatana";
	damage = 45;
}

Projectile* Uchigatana::attack(float x, float y) {
	Projectile* p = new Sword(x, y, game);
	p->vx = 0;
	p->vy = 0;
	p->damage = damage;

	return p;
}