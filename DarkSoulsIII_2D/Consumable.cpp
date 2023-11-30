#include "Consumable.h"

Consumable::Consumable(string filename, float x, float y, int width, int height, Game* game) :
	Actor(filename, x, y, width, height, game)
{
}

void Consumable::draw(float scrollX, float scrollY)
{
	Actor::draw(0, 0);
}

void Consumable::consume()
{
	cout << "Consumed" << endl;
}