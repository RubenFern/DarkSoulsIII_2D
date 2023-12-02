#pragma once

#define LIFE 250
#define TOTAL_CONSUMABLES 4
#define TOTAL_WEAPONS 1

#include "Actor.h"
#include "Projectile.h"
#include "Sword.h"
#include "Animation.h"
#include "HealthBar.h"
#include "Consumable.h"
#include "Text.h"
#include "EstusFlask.h"
#include "Weapon.h"
#include "Uchigatana.h"
#include "BloodGem.h"
#include "UchigatanaBleeding.h"
#include "FireGem.h"
#include "FreezeGem.h"
#include "FireKeeper.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* attack();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void loseLife(int damage);
	void restoreLife();
	void loadConsumables();
	void nextConsumable();
	void loadWeapons();
	void nextWeapon();
	void loadCurrentWeapon();
	void setSelectedWeapon(Weapon* weapon);
	void interact(FireKeeper* fireKeeper);

	int life = LIFE;
	int invulnerableTime = 0;
	int orientation;
	int state;
	int souls = 0;

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
	Consumable* selectedConsumable;
	Weapon* selectedWeapon;

	Consumable* consumables[TOTAL_CONSUMABLES];
	int indexConsumables = 0;
	Weapon* weapons[TOTAL_WEAPONS];
	int indexWeapons = 0;
};