#include "Circular.h"
#include "GameLayer.h"
#include "Player.h"

int widthArray[] = { 110, 110, 105, 106 };
int heightArray[] = { 48, 48, 68, 63 };

Circular::Circular(Game* game)
	: Attack("blaidd/attack/1", widthArray, heightArray, 6, game)
{
	damage = 90;
}

Projectile* Circular::attack(int x, int y, int orientation)
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

	Player* player = static_cast<GameLayer*>(game->gameLayer)->player;

	player->timeFreeze = timeFreeze;

	return p;
}