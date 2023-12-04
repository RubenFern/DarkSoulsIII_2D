#include "Magic.h"

int widthArray3[] = { 36, 36, 50, 50 };
int heightArray3[] = { 46, 46, 44, 45 };

Magic::Magic(Game* game)
	: Attack("blaidd/attack/3", widthArray3, heightArray3, 6, game)
{
	distanceAttack = 100;
	damage = 30;
	cadence = 40;
}

Projectile* Magic::attack(int x, int y, int orientation)
{
	Projectile* p = new FireBall(x, y, game);

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