#include "BloodGem.h"
#include "Player.h"
#include "GameLayer.h"

BloodGem::BloodGem(float x, float y, Game* game) :
	Consumable("res/actors/objects/bloodgem.jpg", x, y, 80, 82, game)
{
	text = new Text(to_string(num), WIDTH * 0.04, HEIGHT * 0.85, game);
}

void BloodGem::update()
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

void BloodGem::consume()
{
	if (num == 0)
		return;

	isUsing = true;

	Player* player = static_cast<GameLayer*>(game->gameLayer)->player;

	UchigatanaBleeding* ub = new UchigatanaBleeding(WIDTH * 0.13, HEIGHT * 0.90, game);
	ub->setDamage(50);
	ub->stateBleeding = true;
	ub->stateFreezing = false;

	num--;
	text->content = std::to_string(num);

	player->setSelectedWeapon(ub);
}