#include "EstusFlask.h"
#include "GameLayer.h"
#include "Player.h"

EstusFlask::EstusFlask(float x, float y, Game* game) :
	Consumable("res/actors/objects/estus.jpg", x, y, 70, 80, game)
{
	num = totalEstus;
	text = new Text(to_string(num), WIDTH * 0.04, HEIGHT * 0.85, game);
	name = "Estus";
	pathImage = "estus_icon.jpg";
}

void EstusFlask::consume()
{
	Player* player = static_cast<GameLayer*>(game->gameLayer)->player;

	if (player->life >= LIFE || num == 0)
		return;

	if (player->life + restore >= LIFE)
		player->life = LIFE;
	else
		player->life += restore;

	num--;
	text->content = std::to_string(num);
	player->healthBar->health = player->life;
}