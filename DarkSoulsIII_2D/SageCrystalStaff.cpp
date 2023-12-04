#include "SageCrystalStaff.h"
#include "Player.h"
#include "GameLayer.h"

SageCrystalStaff::SageCrystalStaff(float x, float y, Game* game) :
	Weapon("res/actors/weapons/sagecrystalstaff.png", x, y, 60, 80, game)
{
	path = "sage-crystal-staff";
	damage = 75;
}

Projectile* SageCrystalStaff::attack(float x, float y) 
{
	Player* player = static_cast<GameLayer*>(game->gameLayer)->player;

	if (player->mana <= 0)
		return NULL;

	Projectile* p = new MagicBall(x, y, game);
	p->vx = 0;
	p->vy = 0;
	p->damage = damage;

	player->mana -= costMana;

	if (player->mana < 0)
		player->mana = 0;
	
	player->manaBar->mana = player->mana;

	return p;
}