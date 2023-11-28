#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Projectile.h"

class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, int width, int height, Game* game);
	virtual Projectile* attack();
	virtual void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	virtual void update();
	virtual void impacted(); // Recibe impacto y pone animación de morir
	virtual void move();
	float vxIntelligence;
	int state;
	int attackCadence = 30;
	int attackTime = 0;
	int life = 3;
	int damage = 20;
	int orientation;
	bool contactDamage;

	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aIdleUp;
	Animation* aIdleDown;

	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aRunningUp;
	Animation* aRunningDown;

	Animation* aAttackingRight;
	Animation* aAttackingLeft;
	Animation* aAttackingUp;
	Animation* aAttackingDown;

	Animation* aDeath;

	Animation* animation; // Referencia a la animación mostrada
};