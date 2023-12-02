#pragma once

#define ERROR 50
#define VISION_FIELD 175

#include "Actor.h"
#include "Animation.h"
#include "Projectile.h"
#include "HealthBar.h"
#include "Point.h"
#include "Player.h"

class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, int width, int height, Game* game);
	virtual Projectile* attack();
	virtual void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	virtual void update();
	virtual void impacted(Player* player); // Recibe impacto y pone animación de morir
	virtual void move();
	float vxIntelligence;
	int state;
	int attackCadence = 30;
	int attackTime = 0;
	int life = 3;
	int damage = 20;
	int orientation;
	bool contactDamage;
	int numberOfImpacts;
	int freezeTime = 0;
	int soulsValue = 0;

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

	HealthBar* healthBar;
};