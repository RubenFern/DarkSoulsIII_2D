#pragma once

#define LIFE 250
#define MANA 150
#define TOTAL_CONSUMABLES 4
#define TOTAL_WEAPONS 2

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
#include "SageCrystalStaff.h"
#include "ManaBar.h"

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
	int getDamage();

	int maxLife = LIFE;
	int maxMana = MANA;
	int life = maxLife;
	int mana = maxMana;
	int invulnerableTime = 0;
	int orientation;
	int state;
	int souls = 0;
	int damageBase = 0;
	int timeFreeze = 0;

	int costSoulsUpLife = 100;
	int costSoulsUpMana = 100;
	int costSoulsUpDamage = 100;

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
	ManaBar* manaBar;
	Consumable* selectedConsumable;
	Weapon* selectedWeapon;

	Consumable* consumables[TOTAL_CONSUMABLES];
	int indexConsumables = 0;
	Weapon* weapons[TOTAL_WEAPONS];
	int indexWeapons = 0;
};