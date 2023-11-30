#include "Uchigatana.h"

Uchigatana::Uchigatana(float x, float y, Game* game) :
	Weapon("res/actors/objects/uchigatana.jpg", x, y, 60, 80, game)
{
	path = "player-katana";
	damage = 45;
}