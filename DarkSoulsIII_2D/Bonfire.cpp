#include "Bonfire.h"

Bonfire::Bonfire(float x, float y, Game* game) :
	Tile("", x, y, game) 
{
	animation = new Animation("res/actors/objects/bonfire.png", 65, 77, 347, 77, 4, 4, true, game);
}

void Bonfire::draw(float scrollX, float scrollY) 
{
	animation->update();
	animation->draw(x - scrollX, y - scrollY);
}