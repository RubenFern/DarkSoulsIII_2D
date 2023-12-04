#include "Thrust.h"

int widthArray2[] = { 73, 73, 39, 35 };
int heightArray2[] = { 48, 48, 74, 68 };

Thrust::Thrust(Game* game)
	: Attack("blaidd/attack/2", widthArray2, heightArray2, 6, game)
{
	distanceAttack = 40;
	damage = 60;
	cadence = 40;
}

Projectile* Thrust::attack(int x, int y, int orientation)
{
	Projectile* p = new Sword(x, y, game);

	float vx = 0, vy = 0;

	if (orientation == game->orientationLeft)
		vx = -4;
	else if (orientation == game->orientationDown)
		vy = 4;
	else if (orientation == game->orientationUp)
		vy = -4;
	else if (orientation == game->orientationRight)
		vx = 4;

	p->vx = vx;
	p->vy = vy;

	return p;
}