#pragma once

#define WIDTH_IDLE_U_L_R 34
#define HEIGHT_IDLE_U_L_R 53
#define WIDTH_IDLE_D 36
#define HEIGHT_IDLE_D 54

#include "Enemy.h"
#include "Animation.h"

class Archer : public Enemy
{
public:
	Archer(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update() override;
	void impacted() override; // Recibe impacto y pone animación de morir
};

