#include "MenuUpLevel.h"
#include "GameLayer.h"

MenuUpLevel::MenuUpLevel(Game* game)
	: Actor("res/menu/up-level.png", WIDTH / 2, HEIGHT / 2, WIDTH_MENU, HEIGHT_MENU, game) 
{
	title = new Text("Selecciona la acción que quieras realizar", WIDTH * 0.45, HEIGHT * 0.30, game);

	options[0] = new Text("2.  Aumentar barra de vida", WIDTH * 0.38, HEIGHT * 0.40, game);
	options[1] = new Text("3.  Aumentar barra de magia", WIDTH * 0.388, HEIGHT * 0.45, game);
	options[2] = new Text("4.  Aumentar ataque base", WIDTH * 0.378, HEIGHT * 0.50, game);
	options[3] = new Text("5.  Salir", WIDTH * 0.30, HEIGHT * 0.55, game);

	stats[0] = new Text("Vida: ", WIDTH * 0.67, HEIGHT * 0.40, game);
	stats[1] = new Text("Magia: ", WIDTH * 0.675, HEIGHT * 0.45, game);
	stats[2] = new Text("Ataque: ", WIDTH * 0.674, HEIGHT * 0.50, game);
}

void MenuUpLevel::draw(float scrollX, float scrollY)
{
	Actor::draw(scrollX, scrollY);

	title->draw();

	for (int i = 0; i < OPTIONS; i++)
		options[i]->draw();

	if (player == nullptr)
		player = static_cast<GameLayer*>(game->gameLayer)->player;

	stats[0]->content = "Vida: " + to_string(player->life);
	stats[1]->content = "Magia: " + to_string(player->mana);
	stats[2]->content = "Ataque: " + to_string(player->damageBase);

	for (int i = 0; i < STATS; i++)
		stats[i]->draw();
}