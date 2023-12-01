#include "BloodGem.h"

BloodGem::BloodGem(float x, float y, Game* game) :
	Consumable("res/actors/objects/bloodgem.jpg", x, y, 80, 82, game)
{
}

void BloodGem::draw(float scrollX, float scrollY)
{
	Actor::draw(0, 0);

	useTime--;
}

void BloodGem::consume()
{
	
}