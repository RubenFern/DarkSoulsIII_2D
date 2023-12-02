#include "FreezeGem.h"
#include "Player.h"
#include "GameLayer.h"

FreezeGem::FreezeGem(float x, float y, Game* game) :
	Consumable("res/actors/objects/freezegem.jpg", x, y, 80, 80, game)
{
	text = new Text(to_string(num), WIDTH * 0.04, HEIGHT * 0.85, game);
}

void FreezeGem::update()
{
	if (isUsing)
	{
		useTime--;

		if (useTime == 0)
		{
			isUsing = false;
			useTime = TIME;

			Player* player = static_cast<GameLayer*>(game->gameLayer)->player;
			player->setSelectedWeapon(player->weapons[0]);
		}
	}
}

void FreezeGem::consume()
{
	if (num == 0)
		return;

	isUsing = true;

	Player* player = static_cast<GameLayer*>(game->gameLayer)->player;

	UchigatanaFreezing* uf = new UchigatanaFreezing(WIDTH * 0.13, HEIGHT * 0.90, game);
	uf->setDamage(50);
	uf->stateBleeding = false;
	uf->stateFreezing = true;

	player->setSelectedWeapon(uf);
}