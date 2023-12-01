#include "Uchigatana.h"

Uchigatana::Uchigatana(float x, float y, Game* game) :
	Weapon("res/actors/weapons/uchigatana.jpg", x, y, 60, 80, game)
{
	path = "uchigatana";
	damage = 45;
}