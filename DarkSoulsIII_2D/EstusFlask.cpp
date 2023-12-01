#include "EstusFlask.h"
#include "GameLayer.h"
#include "Player.h"

EstusFlask::EstusFlask(float x, float y, Game* game) :
	Consumable("res/actors/objects/estus.jpg", x, y, 70, 80, game)
{
	textNumEstus = new Text(to_string(numEstus), WIDTH * 0.04, HEIGHT * 0.85, game);
}

void EstusFlask::draw(float scrollX, float scrollY)
{
	Actor::draw(0, 0);

	textNumEstus->draw();
}

void EstusFlask::consume()
{
	Player* player = static_cast<GameLayer*>(game->gameLayer)->player;

	if (player->life >= LIFE || numEstus == 0)
		return;

	if (player->life + restore >= LIFE)
		player->life = LIFE;
	else
		player->life += restore;

	numEstus--;
	textNumEstus->content = std::to_string(numEstus);
	player->healthBar->health = player->life;
}