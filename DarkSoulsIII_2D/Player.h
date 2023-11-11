#pragma once

#define WIDTH_DOWN 37
#define HEIGHT_DOWN 53
#define WIDTH_UP 37
#define HEIGHT_UP 53
#define WIDTH_LEFT 55
#define HEIGHT_LEFT 53
#define WIDTH_RIGHT 55
#define HEIGHT_RIGHT 53

#define WIDTH_ATTACK_R_L 69
#define HEIGHT_ATTACK_R_L 59
#define WIDTH_ATTACK_U 64
#define HEIGHT_ATTACK_U 66
#define WIDTH_ATTACK_D 72
#define HEIGHT_ATTACK_D 68

#define WIDTH_DEATH 35
#define HEIGHT_DEATH 53

#include "Actor.h"
#include "Projectile.h"
#include "Animation.h" // incluir animacion 

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* attack();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
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

	Animation* aDeath;
	Animation* animation; // Referencia a la animación mostrada
	int attackCadence = 30;
	int attackTime = 0;
};