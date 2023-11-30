#include "EstusFlask.h"
#include "GameLayer.h"
#include "Player.h"

EstusFlask::EstusFlask(float x, float y, Game* game) :
	Consumable("res/actors/objects/estus.jpg", x, y, 70, 80, game)
{
}

void EstusFlask::consume()
{
	Player* player = static_cast<GameLayer*>(game->gameLayer)->player;

	if (player->life >= LIFE || player->numEstus == 0)
		return;

	if (player->life + restore >= LIFE)
		player->life = LIFE;
	else
		player->life += restore;

	player->numEstus--;
	player->textNumEstus->content = std::to_string(player->numEstus);
	player->healthBar->health = player->life;
}