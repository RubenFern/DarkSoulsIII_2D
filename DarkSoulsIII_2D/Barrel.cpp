#include "Barrel.h"

Barrel::Barrel(float x, float y, Game* game) 
	: Tile("", x, y, game)
{
	animation = new Animation("res/actors/objects/barrel.png", 28, 38, 28, 38, 4, 1, true, game);
}

void Barrel::draw(float scrollX, float scrollY)
{
	animation->draw(x - scrollX, y - scrollY);
}

int Barrel::destroy(Player* player)
{
	srand(time(0));
	int index = rand() % 4;

	player->consumables[index]->num++;
	player->consumables[index]->text->content = std::to_string(player->consumables[index]->num);

	return index;
}