#pragma once

#include "Uchigatana.h"

class UchigatanaBleeding : public Uchigatana
{
public:
	UchigatanaBleeding(float x, float y, Game* game);
	int attackCadence = 15;
	int attackTime = 0;
};

