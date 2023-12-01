#pragma once

#include "Weapon.h"

class Uchigatana : public Weapon
{
public:
	Uchigatana(float x, float y, Game* game);
	int attackCadence = 15;
	int attackTime = 0;
};

