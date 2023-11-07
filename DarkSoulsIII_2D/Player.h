#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h" // incluir animacion 

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* attack();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0) override; // Va a sobrescribir
	void loseLife();
	int life = 3;
	int invulnerableTime = 0;
	int orientation;
	int state;
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
	Animation* animation; // Referencia a la animación mostrada
	int attackCadence = 30;
	int attackTime = 0;
};