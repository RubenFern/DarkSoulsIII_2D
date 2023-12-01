#include "UchigatanaBleeding.h"

UchigatanaBleeding::UchigatanaBleeding(float x, float y, Game* game) :
	Uchigatana(x, y, game)
{
	path = "uchigatana-bleeding";
	damage = 70;
}